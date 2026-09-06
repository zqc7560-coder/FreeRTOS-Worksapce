/*
 * led_blink.c
 *
 *  Created on: Nov 17, 2025
 *      Author: liuyu
 */

#include "FreeRTOS.h"
#include "stm32f1xx_hal.h"
#include "task.h"
#include "main.h"

void vLEDTask(void *pvParameters)
{
	while(1)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
		vTaskDelay(pdMS_TO_TICKS(100));
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}
