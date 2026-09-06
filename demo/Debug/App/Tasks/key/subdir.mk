################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Tasks/key/key1.c \
../App/Tasks/key/key2.c \
../App/Tasks/key/key3.c \
../App/Tasks/key/key4.c \
../App/Tasks/key/key_up_down.c 

OBJS += \
./App/Tasks/key/key1.o \
./App/Tasks/key/key2.o \
./App/Tasks/key/key3.o \
./App/Tasks/key/key4.o \
./App/Tasks/key/key_up_down.o 

C_DEPS += \
./App/Tasks/key/key1.d \
./App/Tasks/key/key2.d \
./App/Tasks/key/key3.d \
./App/Tasks/key/key4.d \
./App/Tasks/key/key_up_down.d 


# Each subdirectory must supply rules for building sources it contributes
App/Tasks/key/%.o App/Tasks/key/%.su App/Tasks/key/%.cyclo: ../App/Tasks/key/%.c App/Tasks/key/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../FreeRTOS/Inc -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/demo/App" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/demo/App/Drivers" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/demo/App/Tasks" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/demo/App/Tasks/common" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/demo/App/Tasks/key" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/demo/App/Tasks/lcd" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-App-2f-Tasks-2f-key

clean-App-2f-Tasks-2f-key:
	-$(RM) ./App/Tasks/key/key1.cyclo ./App/Tasks/key/key1.d ./App/Tasks/key/key1.o ./App/Tasks/key/key1.su ./App/Tasks/key/key2.cyclo ./App/Tasks/key/key2.d ./App/Tasks/key/key2.o ./App/Tasks/key/key2.su ./App/Tasks/key/key3.cyclo ./App/Tasks/key/key3.d ./App/Tasks/key/key3.o ./App/Tasks/key/key3.su ./App/Tasks/key/key4.cyclo ./App/Tasks/key/key4.d ./App/Tasks/key/key4.o ./App/Tasks/key/key4.su ./App/Tasks/key/key_up_down.cyclo ./App/Tasks/key/key_up_down.d ./App/Tasks/key/key_up_down.o ./App/Tasks/key/key_up_down.su

.PHONY: clean-App-2f-Tasks-2f-key

