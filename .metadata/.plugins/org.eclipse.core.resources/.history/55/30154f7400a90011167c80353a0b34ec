################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/key.c 

OBJS += \
./Drivers/key.o 

C_DEPS += \
./Drivers/key.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/%.o Drivers/%.su Drivers/%.cyclo: ../Drivers/%.c Drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/p3.3 example1/FreeRTOS/Inc" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/p3.3 example1/User/Task" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/p3.3 example1/Drivers" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/p3.3 example1/User/Keys" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers

clean-Drivers:
	-$(RM) ./Drivers/key.cyclo ./Drivers/key.d ./Drivers/key.o ./Drivers/key.su

.PHONY: clean-Drivers

