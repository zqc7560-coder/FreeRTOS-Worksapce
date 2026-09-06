/*
 * RunModePanel.c
 *
 *  Created on: Feb 27, 2026
 *      Author: liuyu
 */
#include "lcd.h"
#include "color.h"
#include "waveform_capturer.h"
#include "lcd_task.h"
#include "FreeRTOS.h"
#include "task.h"

#define SELECTED_INDEX_RUN_MODE 0x00

static int8_t selectedIndex = -1; /* 当前选中的项目序号，负数代表未选中 */

void PanelRunMode_Repaint(void)
{
	// banner，绿色
	lcd_set_cursor(260, 8);
	lcd_set_brush(PANNEL_BANNER_COLOR);
	lcd_fill_rect(60,15);

	// banner标题，橙色
	lcd_set_cursor(262, 21);
	lcd_set_pen(PANNEL_BANNER_TITLE_COLOR);
	lcd_print_string("Run Mode");

	// 面板背景，灰色
	lcd_set_cursor(260, 23);
	lcd_set_brush(PANNEL_BACK_COLOR);
	lcd_fill_rect(60,35);

	// 文字
	lcd_set_pen(PANNEL_TEXT_COLOR);

	// 260 60 run 15
	if(selectedIndex == SELECTED_INDEX_RUN_MODE)
	{
		lcd_set_brush(PANNEL_SELECTED_COLOR);
		lcd_set_cursor(264, 34);
		lcd_fill_rect(51, 11);
	}
	else
	{
		lcd_set_brush(PANNEL_BACK_COLOR);
	}

	lcd_set_cursor(265, 43);

	const char *runModeString;

	if(WaveformCapture_GetRunMode() == 0)
	{
		runModeString = "Running";
	}
	else
	{
		runModeString = "One-shot";
	}

	lcd_print_string(runModeString);
}

void PanelRunMode_Select(void)
{
	/*选中第一个项目*/
	selectedIndex = 0;

	if(WaveformCapture_GetRunMode() == 0)
	{
		WaveformCapture_SetRunMode(1);
	}
	else
	{
		WaveformCapture_SetRunMode(0);
	}
}

void PanelRunMode_Deselect(void)
{
	/* 通过设置一个负数表示当前未选中 */
	selectedIndex = -1;
}

void PanelRunMode_UpDownKey(int Direction, int Repeat)
{
	extern TaskHandle_t lcdTask;

	if(selectedIndex < 0) return;

	if( selectedIndex == SELECTED_INDEX_RUN_MODE)
	{
		if(WaveformCapture_GetRunMode() == 0)
		{
			WaveformCapture_SetRunMode(1);
		}
		else
		{
			WaveformCapture_SetRunMode(0);
		}
	}

	xTaskNotify(lcdTask, RUN_MODE_BANNER_REPAINT_BIT, eSetBits);
}
