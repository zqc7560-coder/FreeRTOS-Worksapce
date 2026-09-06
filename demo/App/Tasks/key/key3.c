/*
 * key3.c
 *
 *  Created on: Feb 26, 2026
 *      Author: liuyu
 */

#include "button.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "lcd_task.h"
#include "buzzer_task.h"

#include "panel_waveform.h"
#include "panel_run_mode.h"
#include "panel_scale.h"
#include "panel_cursor.h"
#include "panel_generator.h"

static Button_TypeDef key3;

static uint32_t GetTickCallback(void);
static uint8_t Key3_ReadPinStateCallback(void);
static void Key3_PressCallback(void);

void Key3_Init(void)
{
	Button_InitTypeDef Button_InitStruct = {0};

	Button_InitStruct.LongPressTime = 1000;
	Button_InitStruct.LongPressRepeatInterval = 100;
	Button_InitStruct.ReadPinStateCallback = Key3_ReadPinStateCallback;
	Button_InitStruct.GetTimeCallback = GetTickCallback;
	Button_InitStruct.ClickedCallback = Key3_PressCallback;
	Button_Init(&key3, &Button_InitStruct);
}

void Key3_Scan(void)
{
	Button_Scan(&key3);
}

static uint32_t GetTickCallback(void)
{
	return pdTICKS_TO_MS(xTaskGetTickCount());
}

static uint8_t Key3_ReadPinStateCallback(void)
{
	return (uint8_t)HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin);
}

//
// @功能：按钮3按下的回调函数，按钮3对应游标面板
//
static void Key3_PressCallback(void)
{
	extern TaskHandle_t lcdTask;

	PanelRunMode_Deselect();
	PanelCursor_Select();
	PanelScale_Deselect();
	PanelGenerator_Deselect();

	xTaskNotify(lcdTask/*xTaskToNotify*/, ALL_BANNER_REPAINT_BIT/*ulValue*/, eSetBits/*eAction*/);

	Buzzer_Beep(100);
}
