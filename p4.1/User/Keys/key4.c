/*
 * key4.c
 *
 *  Created on: Jun 27, 2026
 *      Author: 23224
 */

#include "key.h"
#include <string.h>
#include "buzzer_task.h"

static KeyHandle_TypeDef hkey4;

static void KEY4_ClickedCallback(void);

void Key4_Init(void)
{
	hkey4.GPIO_Port = KEY4_GPIO_Port;
	hkey4.GPIO_Pin = KEY4_Pin;
	hkey4.ClickedCallback = KEY4_ClickedCallback;
	Key_Init(&hkey4);
}

void Key4_Scan(void)
{
	Key_Scan(&hkey4);
}

static void KEY4_ClickedCallback(void)
{
	Buzzer_Beep();
}
