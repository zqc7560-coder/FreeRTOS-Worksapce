/*
 * key_down.c
 *
 *  Created on: Jun 27, 2026
 *      Author: 23224
 */

#include "key.h"
#include <string.h>
#include "buzzer_task.h"

static KeyHandle_TypeDef hkeyDown;

static void KEY_DOWN_ClickedCallback(void);

void KeyDown_Init(void)
{
	hkeyDown.GPIO_Port = KEY_DOWN_GPIO_Port;
	hkeyDown.GPIO_Pin = KEY_DOWN_Pin;
	hkeyDown.ClickedCallback = KEY_DOWN_ClickedCallback;
	Key_Init(&hkeyDown);
}

void KeyDown_Scan(void)
{
	Key_Scan(&hkeyDown);
}

static void KEY_DOWN_ClickedCallback(void)
{
	Buzzer_Beep();
}
