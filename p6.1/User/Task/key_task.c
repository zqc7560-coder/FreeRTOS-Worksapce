/*
 * key_task.c
 *
 *  Created on: Jun 25, 2026
 *      Author: 23224
 */

#include "FreeRTOS.h"
#include "task.h"
#include "key.h"
#include "main.h"
#include <string.h>
#include "key1.h"
#include "key2.h"
#include "key3.h"
#include "key4.h"
#include "key_up.h"
#include "key_down.h"


void vKeyTask(void *pvParameters)
{
	Key1_Init();
	Key2_Init();
	Key3_Init();
	Key4_Init();
	KeyUP_Init();
	KeyDown_Init();

	for(;;)
	{
		Key1_Scan();
		Key2_Scan();
		Key3_Scan();
		Key4_Scan();
		KeyUP_Scan();
		KeyDown_Scan();

		//不能省略，删除掉之后该任务永远都不会进入阻塞状态，导致低优先级的任务无法执行。
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}
