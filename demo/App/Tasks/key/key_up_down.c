/*
 * key_up_down.c
 *
 *  Created on: Feb 26, 2026
 *      Author: liuyu
 */

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "button.h"
#include "waveform_capturer.h"
#include "waveform_generator.h"
#include "buzzer_task.h"

#include "panel_waveform.h"
#include "panel_run_mode.h"
#include "panel_scale.h"
#include "panel_cursor.h"
#include "panel_generator.h"

static Button_TypeDef keyUp;
static Button_TypeDef keyDown;

static uint32_t GetTickCallback(void);
static uint8_t KeyUp_ReadPinStateCallback(void);
static uint8_t KeyDown_ReadPinStateCallback(void);
static void KeyUp_PressCallback(void);
static void KeyDown_PressCallback(void);
static void KeyUp_LongPressedCallback(uint16_t Repeat);
static void KeyDown_LongPressedCallback(uint16_t Repeat);

void KeyUpDown_Init(void)
{
	Button_InitTypeDef Button_InitStruct = {0};

	Button_InitStruct.LongPressTime = 1000;
	Button_InitStruct.LongPressRepeatInterval = 100;
	Button_InitStruct.ReadPinStateCallback = KeyUp_ReadPinStateCallback;
	Button_InitStruct.GetTimeCallback = GetTickCallback;
	Button_InitStruct.ClickedCallback = KeyUp_PressCallback;
	Button_InitStruct.LongPressCallback = KeyUp_LongPressedCallback;
	Button_Init(&keyUp, &Button_InitStruct);

	Button_InitStruct.LongPressTime = 1000;
	Button_InitStruct.LongPressRepeatInterval = 100;
	Button_InitStruct.ReadPinStateCallback = KeyDown_ReadPinStateCallback;
	Button_InitStruct.GetTimeCallback = GetTickCallback;
	Button_InitStruct.ClickedCallback = KeyDown_PressCallback;
	Button_InitStruct.LongPressCallback = KeyDown_LongPressedCallback;
	Button_Init(&keyDown, &Button_InitStruct);
}

void KeyUpDown_Scan(void)
{
	Button_Scan(&keyUp);
	Button_Scan(&keyDown);
}

static uint32_t GetTickCallback(void)
{
	return pdTICKS_TO_MS(xTaskGetTickCount());
}

static uint8_t KeyUp_ReadPinStateCallback(void)
{
	return (uint8_t)HAL_GPIO_ReadPin(KEY_UP_GPIO_Port, KEY_UP_Pin);
}

static uint8_t KeyDown_ReadPinStateCallback(void)
{
	return (uint8_t)HAL_GPIO_ReadPin(KEY_DOWN_GPIO_Port, KEY_DOWN_Pin);
}

static void KeyUp_PressCallback(void)
{
	PanelRunMode_UpDownKey(1, 0);
	PanelScale_UpDownKey(1, 0);
	PanelCursor_UpDownKey(1, 0);
	PanelGenerator_UpDownKey(1, 0);

	Buzzer_Beep(100);
}

static void KeyDown_PressCallback(void)
{
	PanelRunMode_UpDownKey(-1, 0);
	PanelScale_UpDownKey(-1, 0);
	PanelCursor_UpDownKey(-1, 0);
	PanelGenerator_UpDownKey(-1, 0);

	Buzzer_Beep(100);
}

static void KeyUp_LongPressedCallback(uint16_t Repeat)
{
	PanelRunMode_UpDownKey(1, 1);
	PanelScale_UpDownKey(1, 1);
	PanelCursor_UpDownKey(1, 1);
	PanelGenerator_UpDownKey(1, 1);

	if(Repeat == 1)
	{
		Buzzer_Beep(50);
	}
}

static void KeyDown_LongPressedCallback(uint16_t Repeat)
{
	PanelRunMode_UpDownKey(-1, 1);
	PanelScale_UpDownKey(-1, 1);
	PanelCursor_UpDownKey(-1, 1);
	PanelGenerator_UpDownKey(-1, 1);

	if(Repeat == 1)
	{
		Buzzer_Beep(50);
	}
}
