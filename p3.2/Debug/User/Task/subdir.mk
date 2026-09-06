################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/Task/buzzer_task.c \
../User/Task/key_task.c \
../User/Task/lcd_task.c 

OBJS += \
./User/Task/buzzer_task.o \
./User/Task/key_task.o \
./User/Task/lcd_task.o 

C_DEPS += \
./User/Task/buzzer_task.d \
./User/Task/key_task.d \
./User/Task/lcd_task.d 


# Each subdirectory must supply rules for building sources it contributes
User/Task/%.o User/Task/%.su User/Task/%.cyclo: ../User/Task/%.c User/Task/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/p3.2/FreeRTOS/Inc" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/p3.2/User/Task" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/p3.2/Drivers" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/p3.2/User/Keys" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-User-2f-Task

clean-User-2f-Task:
	-$(RM) ./User/Task/buzzer_task.cyclo ./User/Task/buzzer_task.d ./User/Task/buzzer_task.o ./User/Task/buzzer_task.su ./User/Task/key_task.cyclo ./User/Task/key_task.d ./User/Task/key_task.o ./User/Task/key_task.su ./User/Task/lcd_task.cyclo ./User/Task/lcd_task.d ./User/Task/lcd_task.o ./User/Task/lcd_task.su

.PHONY: clean-User-2f-Task

