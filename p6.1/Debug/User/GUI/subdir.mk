################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/GUI/dmm_lable.c 

OBJS += \
./User/GUI/dmm_lable.o 

C_DEPS += \
./User/GUI/dmm_lable.d 


# Each subdirectory must supply rules for building sources it contributes
User/GUI/%.o User/GUI/%.su User/GUI/%.cyclo: ../User/GUI/%.c User/GUI/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/p6.1/FreeRTOS/Inc" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/p6.1/User/Task" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/p6.1/Drivers" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/p6.1/User/Keys" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/p6.1/User" -I"E:/STM 32 Project/FreeRTOS/FreeRTOS Worksapce/p6.1/User/GUI" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-User-2f-GUI

clean-User-2f-GUI:
	-$(RM) ./User/GUI/dmm_lable.cyclo ./User/GUI/dmm_lable.d ./User/GUI/dmm_lable.o ./User/GUI/dmm_lable.su

.PHONY: clean-User-2f-GUI

