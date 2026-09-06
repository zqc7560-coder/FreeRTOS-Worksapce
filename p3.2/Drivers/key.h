/*
 * key.h
 *
 *  Created on: Jun 27, 2026
 *      Author: 23224
 */

#ifndef KEY_H_
#define KEY_H_

#include "main.h"

typedef struct
{
	GPIO_PinState Previous;		//按钮前一时刻的状态
	GPIO_PinState Current;		//按钮当前时刻的状态

	GPIO_TypeDef *GPIO_Port;
	uint16_t GPIO_Pin;

	void (*ClickedCallback)(void);

} KeyHandle_TypeDef;

void Key_Init(KeyHandle_TypeDef *Handle);
void Key_Scan(KeyHandle_TypeDef *Handle);

#endif /* KEY_H_ */
