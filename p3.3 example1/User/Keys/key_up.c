/*
 * key_up.c
 *
 *  Created on: Jun 27, 2026
 *      Author: 23224
 */

#include "key.h"
#include <string.h>
#include "buzzer_task.h"

static KeyHandle_TypeDef hkeyUp;

static void KEY_UP_ClickedCallback(void);

void KeyUP_Init(void)
{
	hkeyUp.GPIO_Port = KEY_UP_GPIO_Port;
	hkeyUp.GPIO_Pin = KEY_UP_Pin;
	hkeyUp.ClickedCallback = KEY_UP_ClickedCallback;
	Key_Init(&hkeyUp);
}

void KeyUP_Scan(void)
{
	Key_Scan(&hkeyUp);
}

static void KEY_UP_ClickedCallback(void)
{
	Buzzer_Beep();
}
