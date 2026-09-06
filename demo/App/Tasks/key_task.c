/*
 * key_task.c
 *
 *  Created on: Nov 29, 2025
 *      Author: liuyu
 */
#include "main.h"
#include "key1.h"
#include "key2.h"
#include "key3.h"
#include "key4.h"
#include "key_up_down.h"
#include "FreeRTOS.h"
#include "task.h"

void vKeyTask(void *pvParameters)
{
	Key1_Init();
	Key2_Init();
	Key3_Init();
	Key4_Init();
	KeyUpDown_Init();

	for(;;)
	{
		Key1_Scan();
		Key2_Scan();
		Key3_Scan();
		Key4_Scan();
		KeyUpDown_Scan();

		vTaskDelay(pdMS_TO_TICKS(10));
	}
}
