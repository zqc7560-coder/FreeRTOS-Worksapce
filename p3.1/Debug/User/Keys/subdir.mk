################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/Keys/key1.c \
../User/Keys/key2.c \
../User/Keys/key3.c \
../User/Keys/key4.c \
../User/Keys/key_down.c \
../User/Keys/key_up.c 

OBJS += \
./User/Keys/key1.o \
./User/Keys/key2.o \
./User/Keys/key3.o \
./User/Keys/key4.o \
./User/Keys/key_down.o \
./User/Keys/key_up.o 

C_DEPS += \
./User/Keys/key1.d \
./User/Keys/key2.d \
./User/Keys/key3.d \
./User/Keys/key4.d \
./User/Keys/key_down.d \
./User/Keys/key_up.d 


# Each subdirectory must supply rules for building sources it contributes
User/Keys/%.o User/Keys/%.su User/Keys/%.cyclo: ../User/Keys/%.c User/Keys/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/p3.1/FreeRTOS/Inc" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/p3.1/User/Task" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/p3.1/Drivers" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/p3.1/User/Keys" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-User-2f-Keys

clean-User-2f-Keys:
	-$(RM) ./User/Keys/key1.cyclo ./User/Keys/key1.d ./User/Keys/key1.o ./User/Keys/key1.su ./User/Keys/key2.cyclo ./User/Keys/key2.d ./User/Keys/key2.o ./User/Keys/key2.su ./User/Keys/key3.cyclo ./User/Keys/key3.d ./User/Keys/key3.o ./User/Keys/key3.su ./User/Keys/key4.cyclo ./User/Keys/key4.d ./User/Keys/key4.o ./User/Keys/key4.su ./User/Keys/key_down.cyclo ./User/Keys/key_down.d ./User/Keys/key_down.o ./User/Keys/key_down.su ./User/Keys/key_up.cyclo ./User/Keys/key_up.d ./User/Keys/key_up.o ./User/Keys/key_up.su

.PHONY: clean-User-2f-Keys

