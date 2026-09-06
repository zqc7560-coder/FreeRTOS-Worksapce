/*
 * key1.c
 *
 *  Created on: Jun 27, 2026
 *      Author: 23224
 */

#include "key.h"
#include <string.h>
#include "buzzer_task.h"

static KeyHandle_TypeDef hkey1;

static void KEY1_ClickedCallback(void);

void Key1_Init(void)
{
	hkey1.GPIO_Port = KEY1_GPIO_Port;
	hkey1.GPIO_Pin = KEY1_Pin;
	hkey1.ClickedCallback = KEY1_ClickedCallback;
	Key_Init(&hkey1);
}

void Key1_Scan(void)
{
	Key_Scan(&hkey1);
}

static void KEY1_ClickedCallback(void)
{
	Buzzer_Beep();
}
