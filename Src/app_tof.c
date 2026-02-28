/**
  ******************************************************************************
  * @file          : app_tof.c
  * @author        : G-DC, Gemini CLI
  * @brief         : Enhanced gesture detection for TeslaBlinker
  ******************************************************************************
  */

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "app_tof.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>

#include "53l7a1_ranging_sensor.h"
#include "app_tof_pin_conf.h"
#include "stm32f4xx_nucleo.h"

/* === Debug Configuration === */
#define DEBUG_LOG_ENABLED 1
#if DEBUG_LOG_ENABLED
  #define LOG_DEBUG(...) printf(__VA_ARGS__)
#else
  #define LOG_DEBUG(...)
#endif

/* === Gesture Detection Configuration === */
#define GESTURE_DIST_THRESHOLD_MM 200   // Max distance for detection
#define GESTURE_MIN_MOVE_ROWS     2.0f  // Minimum rows moved for a gesture
#define GESTURE_MIN_TIME_MS       100   // Too fast is likely noise
#define GESTURE_MAX_TIME_MS       800   // Too slow is likely just moving the hand
#define PULSE_DELAY_MS            100
#define NO_DETECTION_TIMEOUT_MS   500 

#define TIMING_BUDGET (30U) 
#define RANGING_FREQUENCY (30U) 

#define LOW_THRESHOLD  (100U)
#define HIGH_THRESHOLD (200U)

/* Private variables ---------------------------------------------------------*/
static RANGING_SENSOR_Capabilities_t Cap;
static RANGING_SENSOR_ProfileConfig_t Profile;
static RANGING_SENSOR_Result_t Result;
static int32_t status = 0;
volatile uint8_t ToF_EventDetected = 0;

static uint32_t last_detection_time = 0;
static uint8_t no_detection_reported = 0;

typedef enum {
  GESTURE_NONE,
  GESTURE_UP,
  GESTURE_DOWN
} GestureType;

typedef enum {
    GESTURE_STATE_WAIT_ENTRY,
    GESTURE_STATE_TRACK
} GestureState;

static GestureState gesture_state = GESTURE_STATE_WAIT_ENTRY;
static float entry_row_avg = 0.0f;
static uint32_t gesture_start_time = 0;
static uint8_t gesture_reported = 0;

static void send_gpio_pulses(uint8_t count) {
  for (uint8_t i = 0; i < count; i++) {
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
    HAL_Delay(PULSE_DELAY_MS);
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
    HAL_Delay(PULSE_DELAY_MS);
  }
}

/**
 * @brief Calculate the weighted average row (Center of Mass) of detected objects
 */
static float calculate_center_of_mass(RANGING_SENSOR_Result_t *Result, uint8_t *valid_zones) {
    float row_sum = 0;
    int count = 0;
    uint8_t zones_per_line = 8;

    for (uint8_t zone = 0; zone < Result->NumberOfZones; zone++) {
        if (Result->ZoneResult[zone].NumberOfTargets > 0 &&
            Result->ZoneResult[zone].Distance[0] <= GESTURE_DIST_THRESHOLD_MM) {
            row_sum += (float)(zone / zones_per_line);
            count++;
        }
    }

    if (count > 0) {
        *valid_zones = count;
        return row_sum / (float)count;
    }

    *valid_zones = 0;
    return -1.0f;
}

static GestureType detect_gesture(RANGING_SENSOR_Result_t *Result) {
    uint8_t active_zone_count = 0;
    float current_row_avg = calculate_center_of_mass(Result, &active_zone_count);
    uint32_t now = HAL_GetTick();

    switch (gesture_state) {
    case GESTURE_STATE_WAIT_ENTRY:
        if (active_zone_count >= 2) { // Require at least 2 zones for stability
            LOG_DEBUG("[Gesture] Entry detected at CoM Row: %.2f\n\r", current_row_avg);
            entry_row_avg = current_row_avg;
            gesture_start_time = now;
            gesture_reported = 0;
            gesture_state = GESTURE_STATE_TRACK;
        }
        break;

    case GESTURE_STATE_TRACK:
        if (active_zone_count >= 1) {
            float total_move = current_row_avg - entry_row_avg;
            uint32_t duration = now - gesture_start_time;

            if (!gesture_reported && duration >= GESTURE_MIN_TIME_MS) {
                if (duration > GESTURE_MAX_TIME_MS) {
                    LOG_DEBUG("[Gesture] Timed out (slow movement)\n\r");
                    gesture_reported = 1; // Block until hand leaves
                } 
                else if (abs(total_move) >= GESTURE_MIN_MOVE_ROWS) {
                    if (total_move < 0) {
                        LOG_DEBUG("[Gesture] Flick UP detected (%.2f rows in %ldms)\n\r", -total_move, duration);
                        HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
                        send_gpio_pulses(2); // Right blinker
                        HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
                        gesture_reported = 1;
                        return GESTURE_UP;
                    } else {
                        LOG_DEBUG("[Gesture] Flick DOWN detected (%.2f rows in %ldms)\n\r", total_move, duration);
                        HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
                        send_gpio_pulses(1); // Left blinker
                        HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
                        gesture_reported = 1;
                        return GESTURE_DOWN;
                    }
                }
            }
        } else {
            // Hand left detection range
            LOG_DEBUG("[Gesture] Exit. Duration: %ldms\n\r", now - gesture_start_time);
            gesture_state = GESTURE_STATE_WAIT_ENTRY;
        }
        break;

    default:
        gesture_state = GESTURE_STATE_WAIT_ENTRY;
        break;
    }

    return GESTURE_NONE;
}

static void process_gestures(RANGING_SENSOR_Result_t *Result) {
  detect_gesture(Result);
}

static void check_no_detection_timeout(void) {
    uint32_t current_time = HAL_GetTick();
    if ((current_time - last_detection_time) >= NO_DETECTION_TIMEOUT_MS) {
        if (!no_detection_reported) {
            LOG_DEBUG("no detection\n\r");
            gesture_state = GESTURE_STATE_WAIT_ENTRY;
            no_detection_reported = 1;
        }
    }
}

static void MX_53L7A1_ThresholdDetection_Init(void);
static void MX_53L7A1_ThresholdDetection_Process(void);

void MX_TOF_Init(void)
{
  MX_53L7A1_ThresholdDetection_Init();
}

void MX_TOF_Process(void)
{
  MX_53L7A1_ThresholdDetection_Process();
}

static void MX_53L7A1_ThresholdDetection_Init(void)
{
  uint32_t Id;
  RANGING_SENSOR_ITConfig_t ITConfig;

  BSP_COM_Init(COM1);

  HAL_GPIO_WritePin(VL53L7A1_LPn_C_PORT, VL53L7A1_LPn_C_PIN, GPIO_PIN_RESET);
  HAL_Delay(2);
  HAL_GPIO_WritePin(VL53L7A1_LPn_C_PORT, VL53L7A1_LPn_C_PIN, GPIO_PIN_SET);
  HAL_Delay(2);

  printf("\033[2H\033[2J");
  printf("TeslaBlinker: Enhanced Gesture Logic\n\r");

  status = VL53L7A1_RANGING_SENSOR_Init(VL53L7A1_DEV_CENTER);
  if (status != BSP_ERROR_NONE) {
    printf("VL53L7A1_RANGING_SENSOR_Init failed\n\r");
    send_gpio_pulses(3);
    return;
  }

  VL53L7A1_RANGING_SENSOR_ReadID(VL53L7A1_DEV_CENTER, &Id);
  VL53L7A1_RANGING_SENSOR_GetCapabilities(VL53L7A1_DEV_CENTER, &Cap);

  Profile.RangingProfile = RS_PROFILE_8x8_CONTINUOUS;
  Profile.TimingBudget = TIMING_BUDGET;
  Profile.Frequency = RANGING_FREQUENCY;
  Profile.EnableAmbient = 0;
  Profile.EnableSignal = 0;

  VL53L7A1_RANGING_SENSOR_ConfigProfile(VL53L7A1_DEV_CENTER, &Profile);

  ITConfig.Criteria = RS_IT_IN_WINDOW;
  ITConfig.LowThreshold = LOW_THRESHOLD;
  ITConfig.HighThreshold = HIGH_THRESHOLD;

  VL53L7A1_RANGING_SENSOR_ConfigIT(VL53L7A1_DEV_CENTER, &ITConfig);

  status = VL53L7A1_RANGING_SENSOR_Start(VL53L7A1_DEV_CENTER, RS_MODE_ASYNC_CONTINUOUS);
  if (status != BSP_ERROR_NONE) {
    printf("VL53L7A1_RANGING_SENSOR_Start failed\n\r");
    return;
  }

  printf("TeslaBlinker: Ready. CoM tracking enabled.\n\r");

  last_detection_time = HAL_GetTick();
  no_detection_reported = 0;
}

static void MX_53L7A1_ThresholdDetection_Process(void)
{
    if (ToF_EventDetected != 0)
    {
      ToF_EventDetected = 0;
      last_detection_time = HAL_GetTick();
      no_detection_reported = 0;

      status = VL53L7A1_RANGING_SENSOR_GetDistance(VL53L7A1_DEV_CENTER, &Result);
      if (status == BSP_ERROR_NONE)
      {
        process_gestures(&Result);
      }
    }
    else
    {
      check_no_detection_timeout();
    }
}

#ifdef __cplusplus
}
#endif
