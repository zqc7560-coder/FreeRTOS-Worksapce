################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Tasks/common/jadc.c \
../App/Tasks/common/waveform_capturer.c \
../App/Tasks/common/waveform_generator.c 

OBJS += \
./App/Tasks/common/jadc.o \
./App/Tasks/common/waveform_capturer.o \
./App/Tasks/common/waveform_generator.o 

C_DEPS += \
./App/Tasks/common/jadc.d \
./App/Tasks/common/waveform_capturer.d \
./App/Tasks/common/waveform_generator.d 


# Each subdirectory must supply rules for building sources it contributes
App/Tasks/common/%.o App/Tasks/common/%.su App/Tasks/common/%.cyclo: ../App/Tasks/common/%.c App/Tasks/common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../FreeRTOS/Inc -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/demo/App" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/demo/App/Drivers" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/demo/App/Tasks" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/demo/App/Tasks/common" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/demo/App/Tasks/key" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/demo/App/Tasks/lcd" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-App-2f-Tasks-2f-common

clean-App-2f-Tasks-2f-common:
	-$(RM) ./App/Tasks/common/jadc.cyclo ./App/Tasks/common/jadc.d ./App/Tasks/common/jadc.o ./App/Tasks/common/jadc.su ./App/Tasks/common/waveform_capturer.cyclo ./App/Tasks/common/waveform_capturer.d ./App/Tasks/common/waveform_capturer.o ./App/Tasks/common/waveform_capturer.su ./App/Tasks/common/waveform_generator.cyclo ./App/Tasks/common/waveform_generator.d ./App/Tasks/common/waveform_generator.o ./App/Tasks/common/waveform_generator.su

.PHONY: clean-App-2f-Tasks-2f-common

