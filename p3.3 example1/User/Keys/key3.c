/*
 * key3.c
 *
 *  Created on: Jun 27, 2026
 *      Author: 23224
 */

#include "key.h"
#include <string.h>
#include "buzzer_task.h"

static KeyHandle_TypeDef hkey3;

static void KEY3_ClickedCallback(void);

void Key3_Init(void)
{
	hkey3.GPIO_Port = KEY3_GPIO_Port;
	hkey3.GPIO_Pin = KEY3_Pin;
	hkey3.ClickedCallback = KEY3_ClickedCallback;
	Key_Init(&hkey3);
}

void Key3_Scan(void)
{
	Key_Scan(&hkey3);
}

static void KEY3_ClickedCallback(void)
{
	Buzzer_Beep();
}
