################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Tasks/buzzer_task.c \
../App/Tasks/key_task.c \
../App/Tasks/lcd_task.c \
../App/Tasks/led_task.c 

OBJS += \
./App/Tasks/buzzer_task.o \
./App/Tasks/key_task.o \
./App/Tasks/lcd_task.o \
./App/Tasks/led_task.o 

C_DEPS += \
./App/Tasks/buzzer_task.d \
./App/Tasks/key_task.d \
./App/Tasks/lcd_task.d \
./App/Tasks/led_task.d 


# Each subdirectory must supply rules for building sources it contributes
App/Tasks/%.o App/Tasks/%.su App/Tasks/%.cyclo: ../App/Tasks/%.c App/Tasks/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../FreeRTOS/Inc -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/demo/App" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/demo/App/Drivers" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/demo/App/Tasks" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/demo/App/Tasks/common" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/demo/App/Tasks/key" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/demo/App/Tasks/lcd" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-App-2f-Tasks

clean-App-2f-Tasks:
	-$(RM) ./App/Tasks/buzzer_task.cyclo ./App/Tasks/buzzer_task.d ./App/Tasks/buzzer_task.o ./App/Tasks/buzzer_task.su ./App/Tasks/key_task.cyclo ./App/Tasks/key_task.d ./App/Tasks/key_task.o ./App/Tasks/key_task.su ./App/Tasks/lcd_task.cyclo ./App/Tasks/lcd_task.d ./App/Tasks/lcd_task.o ./App/Tasks/lcd_task.su ./App/Tasks/led_task.cyclo ./App/Tasks/led_task.d ./App/Tasks/led_task.o ./App/Tasks/led_task.su

.PHONY: clean-App-2f-Tasks

