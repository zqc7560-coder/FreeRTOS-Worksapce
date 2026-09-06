/*
 * buzzer_task.c
 *
 *  Created on: Mar 1, 2026
 *      Author: liuyu
 */

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "main.h"
#include "jadc.h"

#define BUZZER_COMMAND_BEEP  0x00 /* 蜂鸣器鸣叫一次，长度由参数决定 */
#define BUZZER_COMMAND_BEEP3 0x01 /* 蜂鸣器鸣叫3次 */

typedef struct
{
	uint32_t Command;
	uint32_t Parameter;

} BuzzerCommandTypeDef;

static QueueHandle_t xBuzzerCommandQueue;

void Buzzer_Init(void)
{
	xBuzzerCommandQueue = xQueueCreate(5, sizeof(BuzzerCommandTypeDef *));
}

void Buzzer_Beep(uint32_t Period)
{
	BuzzerCommandTypeDef *pxCommand = (BuzzerCommandTypeDef*)pvPortMalloc(sizeof(BuzzerCommandTypeDef));

	pxCommand->Command = BUZZER_COMMAND_BEEP;
	pxCommand->Parameter = 50;

	xQueueSend(xBuzzerCommandQueue, &pxCommand, 0);
}

void Buzzer_Beep3(void)
{
	BuzzerCommandTypeDef *pxCommand = (BuzzerCommandTypeDef*)pvPortMalloc(sizeof(BuzzerCommandTypeDef));

	pxCommand->Command = BUZZER_COMMAND_BEEP3;

	xQueueSend(xBuzzerCommandQueue, &pxCommand, 0);
}

void vBuzzerTask(void *pvParameters)
{
	BuzzerCommandTypeDef *pxCommand;

	for(;;)
	{
		if(xQueueReceive(xBuzzerCommandQueue, &pxCommand, pdMS_TO_TICKS(100)) == pdPASS)
		{
			if(pxCommand->Command == BUZZER_COMMAND_BEEP)
			{
				HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);

				vTaskDelay(pdMS_TO_TICKS(pxCommand->Parameter));

				HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);

				vTaskDelay(pdMS_TO_TICKS(pxCommand->Parameter));
			}
			else if(pxCommand->Command == BUZZER_COMMAND_BEEP3)
			{
				HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);

				vTaskDelay(pdMS_TO_TICKS(50));

				HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);

				vTaskDelay(pdMS_TO_TICKS(50));
			}

			vPortFree(pxCommand);
		}

//		if()
	}
}
