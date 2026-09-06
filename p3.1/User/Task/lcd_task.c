/*
 * lcd_task.c
 *
 *  Created on: Sep 5, 2026
 *      Author: 23224
 */

#include "main.h"

static void BacklightControl(uint8_t on);
static void Reset(void);

void LCDTask_Init(void)
{
	BacklightControl(1);
	Reset();
}

//
// @作用：控制LED的背光
// @参数：On 0-熄灭背光 1-点亮背光
//
static void BacklightControl(uint8_t on)
{
	if(on == 0)
	{
		HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_SET);
	}
}

//
// @作用：复位LCD
//
static void Reset(void)
{
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
	HAL_Delay(5);
}
