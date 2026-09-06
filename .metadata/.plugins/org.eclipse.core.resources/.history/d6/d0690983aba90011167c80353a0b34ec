/*
 * buzzer_task.c
 *
 *  Created on: Sep 5, 2026
 *      Author: 23224
 */

#include "FreeRTOS.h"
#include "semphr.h"
#include "main.h"

static SemaphoreHandle_t xBuzzerSemphr;

void Buzzer_Init()
{
	//xBuzzerSemphr = xSemaphoreCreateBinary();	//创建二进制信号量
	xBuzzerSemphr = xSemaphoreCreateCounting(10,0);		//创建计数信号量
}

void vBuzzerTask(void *pvParameters)
{
	for(;;)
	{
		xSemaphoreTake(xBuzzerSemphr, portMAX_DELAY);

		HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);
		vTaskDelay(pdMS_TO_TICKS(100));
		HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
	}
}

void Buzzer_Beep()
{
	xSemaphoreGive(xBuzzerSemphr);
}
