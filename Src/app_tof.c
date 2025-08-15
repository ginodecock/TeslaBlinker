/**
  ******************************************************************************
  * @file          : app_tof.c
  * @author        : G-DC
  * @brief         : App for detecting gestures to control blinker
  ******************************************************************************
  *
  * This software is provided AS-IS.
  *
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



/* === Gesture Detection Configuration === */
#define GESTURE_START_DISTANCE_MM 190
#define GESTURE_CONSECUTIVE_ZONES 2
#define GPIO_PULSE_PIN            GPIO_PIN_5
#define GPIO_PULSE_PORT           GPIOA
#define PULSE_DELAY_MS            100
/* Onboard LED definition for Nucleo-F401 */
#define LED1_PIN   GPIO_PIN_5
#define LED1_PORT  GPIOA
#define TIMING_BUDGET (30U) /* 5 ms < TimingBudget < 100 ms */
#define RANGING_FREQUENCY (10U) /* Ranging frequency Hz (shall be consistent with TimingBudget value) */

#define LOW_THRESHOLD  (100U)
#define HIGH_THRESHOLD (330U)

/* Private variables ---------------------------------------------------------*/
static RANGING_SENSOR_Capabilities_t Cap;
static RANGING_SENSOR_ProfileConfig_t Profile;
static RANGING_SENSOR_Result_t Result;
static int32_t status = 0;
volatile uint8_t ToF_EventDetected = 0;

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
static uint8_t entry_row = 255;
static uint8_t last_row = 255;
static GestureType detected_direction = GESTURE_NONE;
static uint8_t gesture_reported = 0;

static void send_gpio_pulses(uint8_t count) {
  for (uint8_t i = 0; i < count; i++) {
    HAL_GPIO_WritePin(GPIO_PULSE_PORT, GPIO_PULSE_PIN, GPIO_PIN_SET);
    HAL_Delay(PULSE_DELAY_MS);
    HAL_GPIO_WritePin(GPIO_PULSE_PORT, GPIO_PULSE_PIN, GPIO_PIN_RESET);
    HAL_Delay(PULSE_DELAY_MS);
  }
}

static GestureType detect_gesture(RANGING_SENSOR_Result_t *Result) {
    uint8_t zones_per_line = 8;
    uint8_t active_row = 255;
    uint8_t in_range = 0;

    // Find first zone within gesture start distance
    for (uint8_t zone = 0; zone < Result->NumberOfZones; zone++) {
        if (Result->ZoneResult[zone].NumberOfTargets > 0 &&
                Result->ZoneResult[zone].Distance[0] <= GESTURE_START_DISTANCE_MM) {
            active_row = zone / zones_per_line;
            in_range = 1;
            break;
        }
    }

    printf("[Gesture] Active row: %d, In range: %d, State: %d\n\r", active_row, in_range, gesture_state);

    switch (gesture_state) {
    case GESTURE_STATE_WAIT_ENTRY:
        if (in_range) {
            // Hand just entered range: initialize entry and last row
            printf("[Gesture] Hand entered detection range at row %d\n\r", active_row);
            entry_row = active_row;
            last_row = active_row;
            detected_direction = GESTURE_NONE;
            gesture_reported = 0;  // Reset reported flag on new entry
            gesture_state = GESTURE_STATE_TRACK;
        }
        break;

    case GESTURE_STATE_TRACK:
        if (in_range) {
            if (active_row != 255 && active_row != last_row) {
                int row_change = active_row - last_row;
                int total_change = active_row - entry_row;

                if (!gesture_reported) {
                    if (abs(total_change) >= GESTURE_CONSECUTIVE_ZONES) {
                        if (row_change < 0) {
                            detected_direction = GESTURE_UP;
                            printf("[Gesture] Detected upward movement (from row %d to row %d)\n\r",
                                last_row, active_row);
                        } else if (row_change > 0) {
                            detected_direction = GESTURE_DOWN;
                            printf("[Gesture] Detected downward movement (from row %d to row %d)\n\r",
                                last_row, active_row);
                        }

                        gesture_reported = 1; // Lock further detection
                    }
                }
                last_row = active_row; // Always update last_row to current row
            } else {
                printf("[Gesture] Hand in range, no significant row change\n\r");
            }
        } else {
            // Hand left detection range: reset everything
            printf("[Gesture] Hand left detection range\n\r");
            if (detected_direction != GESTURE_NONE) {
                GestureType g = detected_direction;
                printf("[Gesture] Gesture completed: %s\n\r",
                    (g == GESTURE_UP) ? "UP" : "DOWN");
                gesture_reported = 0;
                gesture_state = GESTURE_STATE_WAIT_ENTRY;
                return g;
            } else {
                printf("[Gesture] No valid gesture detected before exit\n\r");
                gesture_reported = 0;
                gesture_state = GESTURE_STATE_WAIT_ENTRY;
            }
        }
        break;

    default:
        gesture_state = GESTURE_STATE_WAIT_ENTRY;
        break;
    }

    return GESTURE_NONE;
}


static void process_gestures(RANGING_SENSOR_Result_t *Result) {
  GestureType g = detect_gesture(Result);
  if (g == GESTURE_UP) {
	printf("Upward gesture: 2 GPIO pulses for right blinker\n\r");
	HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_SET);//BSP_LED_On(LED1);
    send_gpio_pulses(2); // Right blinker
    HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_RESET);//BSP_LED_Off(LED1);
  } else if (g == GESTURE_DOWN) {
	printf("Downward gesture: 1 GPIO pulse for left blinker\n\r");
	HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_SET);//BSP_LED_On(LED1);
    send_gpio_pulses(1); // Left blinker
    HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_RESET);//BSP_LED_Off(LED1);
  }
}
static void MX_53L7A1_ThresholdDetection_Init(void);
static void MX_53L7A1_ThresholdDetection_Process(void);
//static void print_result(RANGING_SENSOR_Result_t *Result);

void MX_TOF_Init(void)
{
  MX_53L7A1_ThresholdDetection_Init();
}

/*
 * LM background task
 */
void MX_TOF_Process(void)
{
  MX_53L7A1_ThresholdDetection_Process();
}

static void MX_53L7A1_ThresholdDetection_Init(void)
{
  /* Initialize Virtual COM Port */
  BSP_COM_Init(COM1);

  /* Sensor reset */
  /*HAL_GPIO_WritePin(VL53L7A1_PWR_EN_C_PORT, VL53L7A1_PWR_EN_C_PIN, GPIO_PIN_RESET);
  HAL_Delay(2);
  HAL_GPIO_WritePin(VL53L7A1_PWR_EN_C_PORT, VL53L7A1_PWR_EN_C_PIN, GPIO_PIN_SET);
  HAL_Delay(2);*/
  HAL_GPIO_WritePin(VL53L7A1_LPn_C_PORT, VL53L7A1_LPn_C_PIN, GPIO_PIN_RESET);
  HAL_Delay(4);
  HAL_GPIO_WritePin(VL53L7A1_LPn_C_PORT, VL53L7A1_LPn_C_PIN, GPIO_PIN_SET);
  HAL_Delay(4);

  printf("\033[2H\033[2J");
  printf("Control Tesla Blinker\n\r");
  printf("Sensor initialization...\n\r");

  status = VL53L7A1_RANGING_SENSOR_Init(VL53L7A1_DEV_CENTER);

  if (status != BSP_ERROR_NONE)
  {
    printf("VL53L7A1_RANGING_SENSOR_Init failed\n\r");
    while (1);
  }
}

static void MX_53L7A1_ThresholdDetection_Process(void)
{
  uint32_t Id;

  RANGING_SENSOR_ITConfig_t ITConfig;

  VL53L7A1_RANGING_SENSOR_ReadID(VL53L7A1_DEV_CENTER, &Id);
  VL53L7A1_RANGING_SENSOR_GetCapabilities(VL53L7A1_DEV_CENTER, &Cap);

  Profile.RangingProfile = RS_PROFILE_8x8_CONTINUOUS;
  Profile.TimingBudget = TIMING_BUDGET;
  Profile.Frequency = RANGING_FREQUENCY; /* Ranging frequency Hz (shall be consistent with TimingBudget value) */
  Profile.EnableAmbient = 0; /* Enable: 1, Disable: 0 */
  Profile.EnableSignal = 0; /* Enable: 1, Disable: 0 */

  /* set the profile if different from default one */
  VL53L7A1_RANGING_SENSOR_ConfigProfile(VL53L7A1_DEV_CENTER, &Profile);

  /* threshold parameters */
  ITConfig.Criteria = RS_IT_IN_WINDOW;
  ITConfig.LowThreshold = LOW_THRESHOLD; /* mm */
  ITConfig.HighThreshold = HIGH_THRESHOLD; /* mm */

  VL53L7A1_RANGING_SENSOR_ConfigIT(VL53L7A1_DEV_CENTER, &ITConfig);

  status = VL53L7A1_RANGING_SENSOR_Start(VL53L7A1_DEV_CENTER, RS_MODE_ASYNC_CONTINUOUS);

  if (status != BSP_ERROR_NONE)
  {
    printf("VL53L7A1_RANGING_SENSOR_Start failed\n\r");
    while (1);
  }

  printf("\033[2H\033[2J");
  printf("53L7A1 Threshold Detection demo application\n\r");
  printf("-------------------------------------------\n\n\r");
  printf("please put a target between %d and %d millimeters from the sensor\n\r",
		  LOW_THRESHOLD, HIGH_THRESHOLD);

  while (1)
  {
    /* interrupt mode */
    if (ToF_EventDetected != 0)
    {
      ToF_EventDetected = 0;

      status = VL53L7A1_RANGING_SENSOR_GetDistance(VL53L7A1_DEV_CENTER, &Result);
      if (status == BSP_ERROR_NONE)
      {
        process_gestures(&Result);
      }
    }
  }
}

/*static void print_result(RANGING_SENSOR_Result_t *Result)
{
  int8_t i;
  int8_t j;
  int8_t k;
  int8_t l;
  uint8_t zones_per_line;

  zones_per_line = ((Profile.RangingProfile == RS_PROFILE_8x8_AUTONOMOUS) ||
                    (Profile.RangingProfile == RS_PROFILE_8x8_CONTINUOUS)) ? 8 : 4;

  printf("%c[2H", 27);
  printf("53L7A1 Threshold Detection demo application\n\r");
  printf("-------------------------------------------\n\n\r");

  printf("Cell Format :\n\n\r");
  for (l = 0; l < RANGING_SENSOR_NB_TARGET_PER_ZONE; l++)
  {
    printf(" \033[38;5;10m%20s\033[0m : %20s\n\r", "Distance [mm]", "Status");
    if ((Profile.EnableAmbient != 0) || (Profile.EnableSignal != 0))
    {
      printf(" %20s : %20s\n\r", "Signal [kcps/spad]", "Ambient [kcps/spad]");
    }
  }

  printf("\n\n\r");

  for (j = 0; j < Result->NumberOfZones; j += zones_per_line)
  {
    for (i = 0; i < zones_per_line; i++)
    {
      printf(" -----------------");
    }
    printf("\n\r");

    for (i = 0; i < zones_per_line; i++)
    {
      printf("|                 ");
    }
    printf("|\n\r");

    for (l = 0; l < RANGING_SENSOR_NB_TARGET_PER_ZONE; l++)
    {
      for (k = (zones_per_line - 1); k >= 0; k--)
      {
        if (Result->ZoneResult[j + k].NumberOfTargets > 0)
          printf("| \033[38;5;10m%5ld\033[0m  :  %5ld ",
                 (long)Result->ZoneResult[j + k].Distance[l],
                 (long)Result->ZoneResult[j + k].Status[l]);
        else
          printf("| %5s  :  %5s ", "X", "X");
      }
      printf("|\n\r");

      if ((Profile.EnableAmbient != 0) || (Profile.EnableSignal != 0))
      {
        for (k = (zones_per_line - 1); k >= 0; k--)
        {
          if (Result->ZoneResult[j + k].NumberOfTargets > 0)
          {
            if (Profile.EnableSignal != 0)
            {
              printf("| %5ld  :  ", (long)Result->ZoneResult[j + k].Signal[l]);
            }
            else
              printf("| %5s  :  ", "X");

            if (Profile.EnableAmbient != 0)
            {
              printf("%5ld ", (long)Result->ZoneResult[j + k].Ambient[l]);
            }
            else
              printf("%5s ", "X");
          }
          else
            printf("| %5s  :  %5s ", "X", "X");
        }
        printf("|\n\r");
      }
    }
  }

  for (i = 0; i < zones_per_line; i++)
  {
    printf(" -----------------");
  }
  printf("\n\r");
}*/

#ifdef __cplusplus
}
#endif
