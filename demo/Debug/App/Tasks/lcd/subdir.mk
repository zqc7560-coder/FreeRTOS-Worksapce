################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Tasks/lcd/label_cursor.c \
../App/Tasks/lcd/label_dmm.c \
../App/Tasks/lcd/label_pwr.c \
../App/Tasks/lcd/label_scale.c \
../App/Tasks/lcd/lcd_hardware.c \
../App/Tasks/lcd/panel_cursor.c \
../App/Tasks/lcd/panel_generator.c \
../App/Tasks/lcd/panel_run_mode.c \
../App/Tasks/lcd/panel_scale.c \
../App/Tasks/lcd/panel_waveform.c 

OBJS += \
./App/Tasks/lcd/label_cursor.o \
./App/Tasks/lcd/label_dmm.o \
./App/Tasks/lcd/label_pwr.o \
./App/Tasks/lcd/label_scale.o \
./App/Tasks/lcd/lcd_hardware.o \
./App/Tasks/lcd/panel_cursor.o \
./App/Tasks/lcd/panel_generator.o \
./App/Tasks/lcd/panel_run_mode.o \
./App/Tasks/lcd/panel_scale.o \
./App/Tasks/lcd/panel_waveform.o 

C_DEPS += \
./App/Tasks/lcd/label_cursor.d \
./App/Tasks/lcd/label_dmm.d \
./App/Tasks/lcd/label_pwr.d \
./App/Tasks/lcd/label_scale.d \
./App/Tasks/lcd/lcd_hardware.d \
./App/Tasks/lcd/panel_cursor.d \
./App/Tasks/lcd/panel_generator.d \
./App/Tasks/lcd/panel_run_mode.d \
./App/Tasks/lcd/panel_scale.d \
./App/Tasks/lcd/panel_waveform.d 


# Each subdirectory must supply rules for building sources it contributes
App/Tasks/lcd/%.o App/Tasks/lcd/%.su App/Tasks/lcd/%.cyclo: ../App/Tasks/lcd/%.c App/Tasks/lcd/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../FreeRTOS/Inc -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/demo/App" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/demo/App/Drivers" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/demo/App/Tasks" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/demo/App/Tasks/common" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/demo/App/Tasks/key" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/demo/App/Tasks/lcd" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-App-2f-Tasks-2f-lcd

clean-App-2f-Tasks-2f-lcd:
	-$(RM) ./App/Tasks/lcd/label_cursor.cyclo ./App/Tasks/lcd/label_cursor.d ./App/Tasks/lcd/label_cursor.o ./App/Tasks/lcd/label_cursor.su ./App/Tasks/lcd/label_dmm.cyclo ./App/Tasks/lcd/label_dmm.d ./App/Tasks/lcd/label_dmm.o ./App/Tasks/lcd/label_dmm.su ./App/Tasks/lcd/label_pwr.cyclo ./App/Tasks/lcd/label_pwr.d ./App/Tasks/lcd/label_pwr.o ./App/Tasks/lcd/label_pwr.su ./App/Tasks/lcd/label_scale.cyclo ./App/Tasks/lcd/label_scale.d ./App/Tasks/lcd/label_scale.o ./App/Tasks/lcd/label_scale.su ./App/Tasks/lcd/lcd_hardware.cyclo ./App/Tasks/lcd/lcd_hardware.d ./App/Tasks/lcd/lcd_hardware.o ./App/Tasks/lcd/lcd_hardware.su ./App/Tasks/lcd/panel_cursor.cyclo ./App/Tasks/lcd/panel_cursor.d ./App/Tasks/lcd/panel_cursor.o ./App/Tasks/lcd/panel_cursor.su ./App/Tasks/lcd/panel_generator.cyclo ./App/Tasks/lcd/panel_generator.d ./App/Tasks/lcd/panel_generator.o ./App/Tasks/lcd/panel_generator.su ./App/Tasks/lcd/panel_run_mode.cyclo ./App/Tasks/lcd/panel_run_mode.d ./App/Tasks/lcd/panel_run_mode.o ./App/Tasks/lcd/panel_run_mode.su ./App/Tasks/lcd/panel_scale.cyclo ./App/Tasks/lcd/panel_scale.d ./App/Tasks/lcd/panel_scale.o ./App/Tasks/lcd/panel_scale.su ./App/Tasks/lcd/panel_waveform.cyclo ./App/Tasks/lcd/panel_waveform.d ./App/Tasks/lcd/panel_waveform.o ./App/Tasks/lcd/panel_waveform.su

.PHONY: clean-App-2f-Tasks-2f-lcd

