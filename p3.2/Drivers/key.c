/*
 * key.c
 *
 *  Created on: Jun 27, 2026
 *      Author: 23224
 */

#include "main.h"
#include <string.h>
#include "key.h"

void Key_Init(KeyHandle_TypeDef *Handle)
{
	Handle->Previous = GPIO_PIN_SET;
	Handle->Current = GPIO_PIN_SET;
}

void Key_Scan(KeyHandle_TypeDef *Handle)
{
	Handle->Current = HAL_GPIO_ReadPin(Handle->GPIO_Port, Handle->GPIO_Pin);

	if(Handle->Previous == GPIO_PIN_RESET && Handle->Current == GPIO_PIN_SET)
	{
		Handle->ClickedCallback();
	}

	Handle->Previous = Handle->Current;
}
