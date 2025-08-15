################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
Y:/VM/stm-workspace/TeslaBlinker/Drivers/BSP/Components/vl53l7cx/porting/platform.c \
Y:/VM/stm-workspace/TeslaBlinker/Drivers/BSP/Components/vl53l7cx/vl53l7cx.c \
Y:/VM/stm-workspace/TeslaBlinker/Drivers/BSP/Components/vl53l7cx/modules/vl53l7cx_api.c \
Y:/VM/stm-workspace/TeslaBlinker/Drivers/BSP/Components/vl53l7cx/modules/vl53l7cx_plugin_detection_thresholds.c \
Y:/VM/stm-workspace/TeslaBlinker/Drivers/BSP/Components/vl53l7cx/modules/vl53l7cx_plugin_motion_indicator.c \
Y:/VM/stm-workspace/TeslaBlinker/Drivers/BSP/Components/vl53l7cx/modules/vl53l7cx_plugin_xtalk.c 

OBJS += \
./Drivers/BSP/Components/platform.o \
./Drivers/BSP/Components/vl53l7cx.o \
./Drivers/BSP/Components/vl53l7cx_api.o \
./Drivers/BSP/Components/vl53l7cx_plugin_detection_thresholds.o \
./Drivers/BSP/Components/vl53l7cx_plugin_motion_indicator.o \
./Drivers/BSP/Components/vl53l7cx_plugin_xtalk.o 

C_DEPS += \
./Drivers/BSP/Components/platform.d \
./Drivers/BSP/Components/vl53l7cx.d \
./Drivers/BSP/Components/vl53l7cx_api.d \
./Drivers/BSP/Components/vl53l7cx_plugin_detection_thresholds.d \
./Drivers/BSP/Components/vl53l7cx_plugin_motion_indicator.d \
./Drivers/BSP/Components/vl53l7cx_plugin_xtalk.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/platform.o: Y:/VM/stm-workspace/TeslaBlinker/Drivers/BSP/Components/vl53l7cx/porting/platform.c Drivers/BSP/Components/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../../Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/53L7A1 -I../../Drivers/BSP/Components/vl53l7cx/modules -I../../Drivers/BSP/Components/vl53l7cx/porting -I../../Drivers/BSP/Components/vl53l7cx -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/Components/vl53l7cx.o: Y:/VM/stm-workspace/TeslaBlinker/Drivers/BSP/Components/vl53l7cx/vl53l7cx.c Drivers/BSP/Components/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../../Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/53L7A1 -I../../Drivers/BSP/Components/vl53l7cx/modules -I../../Drivers/BSP/Components/vl53l7cx/porting -I../../Drivers/BSP/Components/vl53l7cx -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/Components/vl53l7cx_api.o: Y:/VM/stm-workspace/TeslaBlinker/Drivers/BSP/Components/vl53l7cx/modules/vl53l7cx_api.c Drivers/BSP/Components/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../../Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/53L7A1 -I../../Drivers/BSP/Components/vl53l7cx/modules -I../../Drivers/BSP/Components/vl53l7cx/porting -I../../Drivers/BSP/Components/vl53l7cx -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/Components/vl53l7cx_plugin_detection_thresholds.o: Y:/VM/stm-workspace/TeslaBlinker/Drivers/BSP/Components/vl53l7cx/modules/vl53l7cx_plugin_detection_thresholds.c Drivers/BSP/Components/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../../Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/53L7A1 -I../../Drivers/BSP/Components/vl53l7cx/modules -I../../Drivers/BSP/Components/vl53l7cx/porting -I../../Drivers/BSP/Components/vl53l7cx -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/Components/vl53l7cx_plugin_motion_indicator.o: Y:/VM/stm-workspace/TeslaBlinker/Drivers/BSP/Components/vl53l7cx/modules/vl53l7cx_plugin_motion_indicator.c Drivers/BSP/Components/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../../Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/53L7A1 -I../../Drivers/BSP/Components/vl53l7cx/modules -I../../Drivers/BSP/Components/vl53l7cx/porting -I../../Drivers/BSP/Components/vl53l7cx -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/Components/vl53l7cx_plugin_xtalk.o: Y:/VM/stm-workspace/TeslaBlinker/Drivers/BSP/Components/vl53l7cx/modules/vl53l7cx_plugin_xtalk.c Drivers/BSP/Components/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../../Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/53L7A1 -I../../Drivers/BSP/Components/vl53l7cx/modules -I../../Drivers/BSP/Components/vl53l7cx/porting -I../../Drivers/BSP/Components/vl53l7cx -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components

clean-Drivers-2f-BSP-2f-Components:
	-$(RM) ./Drivers/BSP/Components/platform.cyclo ./Drivers/BSP/Components/platform.d ./Drivers/BSP/Components/platform.o ./Drivers/BSP/Components/platform.su ./Drivers/BSP/Components/vl53l7cx.cyclo ./Drivers/BSP/Components/vl53l7cx.d ./Drivers/BSP/Components/vl53l7cx.o ./Drivers/BSP/Components/vl53l7cx.su ./Drivers/BSP/Components/vl53l7cx_api.cyclo ./Drivers/BSP/Components/vl53l7cx_api.d ./Drivers/BSP/Components/vl53l7cx_api.o ./Drivers/BSP/Components/vl53l7cx_api.su ./Drivers/BSP/Components/vl53l7cx_plugin_detection_thresholds.cyclo ./Drivers/BSP/Components/vl53l7cx_plugin_detection_thresholds.d ./Drivers/BSP/Components/vl53l7cx_plugin_detection_thresholds.o ./Drivers/BSP/Components/vl53l7cx_plugin_detection_thresholds.su ./Drivers/BSP/Components/vl53l7cx_plugin_motion_indicator.cyclo ./Drivers/BSP/Components/vl53l7cx_plugin_motion_indicator.d ./Drivers/BSP/Components/vl53l7cx_plugin_motion_indicator.o ./Drivers/BSP/Components/vl53l7cx_plugin_motion_indicator.su ./Drivers/BSP/Components/vl53l7cx_plugin_xtalk.cyclo ./Drivers/BSP/Components/vl53l7cx_plugin_xtalk.d ./Drivers/BSP/Components/vl53l7cx_plugin_xtalk.o ./Drivers/BSP/Components/vl53l7cx_plugin_xtalk.su

.PHONY: clean-Drivers-2f-BSP-2f-Components

