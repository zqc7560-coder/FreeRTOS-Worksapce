/*
 * key2.c
 *
 *  Created on: Jun 27, 2026
 *      Author: 23224
 */

#include "key.h"
#include <string.h>
#include "buzzer_task.h"

static KeyHandle_TypeDef hkey2;

static void KEY2_ClickedCallback(void);

void Key2_Init(void)
{
	hkey2.GPIO_Port = KEY2_GPIO_Port;
	hkey2.GPIO_Pin = KEY2_Pin;
	hkey2.ClickedCallback = KEY2_ClickedCallback;
	Key_Init(&hkey2);
}

void Key2_Scan(void)
{
	Key_Scan(&hkey2);
}

static void KEY2_ClickedCallback(void)
{
	Buzzer_Beep();
}
