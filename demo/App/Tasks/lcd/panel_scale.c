/*
 * scale_panel.c
 *
 *  Created on: Feb 27, 2026
 *      Author: liuyu
 */
#include "lcd.h"
#include "color.h"
#include "lcd_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "panel_waveform.h"
#include "waveform_capturer.h"

#define SELECTED_INDEX_SCALE_X 0x00
#define SELECTED_INDEX_SCALE_Y 0x01
#define SELECTED_INDEX_X_POS   0x02

static int8_t selectedIndex = -1; /* 当前选中的项目序号，负数代表未选中 */
static float xScale = 500.0e-6f; // x轴向缩放比，默认500us/格
static float yScale = 1.0f;      // y轴向缩放比，默认1v/格
static uint16_t xOffset = 0; // 波形显示的起始位置，单位点

static void ChangeXScale(int Direction);
static void ChangeYScale(int Direction);
static void ChangeXOffset(int Direction);

void PanelScale_Repaint(void)
{
	// banner，绿色
	lcd_set_cursor(260, 67);
	lcd_set_brush(PANNEL_BANNER_COLOR);
	lcd_fill_rect(60,15);

	// banner标题，橙色
	lcd_set_cursor(275, 80);
	lcd_set_pen(PANNEL_BANNER_TITLE_COLOR);
	lcd_print_string("Scale");

	// 面板背景，灰色
	lcd_set_cursor(260, 82);
	lcd_set_brush(PANNEL_BACK_COLOR);
	lcd_fill_rect(60,35);

	// 文字
	lcd_set_pen(PANNEL_TEXT_COLOR);

	// XScale被选中，绘制选中标记
	if(selectedIndex == SELECTED_INDEX_SCALE_X)
	{
		lcd_set_cursor(274, 89);
		lcd_set_brush(PANNEL_SELECTED_COLOR);
		lcd_fill_rect(9, 11);
	}
	else
	{
		lcd_set_brush(PANNEL_BACK_COLOR);
	}

	lcd_set_cursor(275, 98);
	lcd_print_string("x");

	// YScale被选中，绘制选中标记
	if(selectedIndex == SELECTED_INDEX_SCALE_Y)
	{
		lcd_set_cursor(294, 89);
		lcd_set_brush(PANNEL_SELECTED_COLOR);
		lcd_fill_rect(9, 11);
	}
	else
	{
		lcd_set_brush(PANNEL_BACK_COLOR);
	}

	lcd_set_cursor(295, 98);
	lcd_print_string("y");

	// x_Pos被选中，绘制选中标记
	if(selectedIndex == SELECTED_INDEX_X_POS)
	{
		lcd_set_cursor(273, 99);
		lcd_set_brush(PANNEL_SELECTED_COLOR);
		lcd_fill_rect(37, 11);
	}
	else
	{
		lcd_set_brush(PANNEL_BACK_COLOR);
	}

	lcd_set_cursor(274, 108);
	lcd_print_string("x_pos");
}

void PanelScale_Select(void)
{
	/* 之前未选中 */
	if(selectedIndex < 0)
	{
		/*选中第一个项目*/
		selectedIndex = 0;
	}
	else /* 之前已选中 */
	{
		selectedIndex++;

		/* 超出范围后回滚到0 */
		if(selectedIndex >= 3)
		{
			selectedIndex -= 3;
		}
	}
}

void PanelScale_Deselect(void)
{
	/* 通过设置一个负数表示当前未选中 */
	selectedIndex = -1;
}

//
// @功能：获取X轴向缩放比
// @返回：X轴向缩放比，单位s/格
//
float GetXScale(void)
{
	return xScale;
}

float GetYScale(void)
{
	return yScale;
}

uint16_t GetXOffset(void)
{
	return xOffset;
}

void PanelScale_UpDownKey(int Direction, int Repeat)
{
	extern TaskHandle_t lcdTask;

	if( selectedIndex < 0 ) return;

	if( selectedIndex == SELECTED_INDEX_SCALE_X )
	{
		ChangeXScale(Direction);
	}
	else if( selectedIndex == SELECTED_INDEX_SCALE_Y )
	{
		ChangeYScale(-Direction);
	}
	else if( selectedIndex == SELECTED_INDEX_X_POS )
	{
		ChangeXOffset(-Direction);
	}

	xTaskNotify(lcdTask/*xTaskToNotify*/,
				SCALE_BANNER_REPAINT_BIT | WAVEFORM_REPAINT_BIT | CURSOR_LABEL_REPAINT_BIT | SCALE_LABEL_REPAINT_BIT/*ulValue*/,
				eSetBits/*eAction*/);

}

static void ChangeXScale(int Direction)
{
	static int8_t index = 5;
	static const float list[] = {10.0e-6f, 20.0e-6f, 50.0e-6f, 100.0e-6f,200.0e-6f, 500.0e-6f, 1.0e-3f, 2.0e-3f, 5.0e-3f, 10.0e-3f, 20.0e-3f,50.0e-3f, 100.0e-3f, 200.0e-3f, 500.0e-3f};

	uint16_t length = sizeof(list) / sizeof(float);

	index = (index + Direction + length) % length;

	xScale = list[index];

	WaveformCapture_SetSampleRateFromXScale(xScale);
}

static void ChangeYScale(int Direction)
{
	static uint8_t index = 9;
	static const float list[] = {1.0e-3f, 2.0e-3f, 5.0e-3f, 10.0e-3f, 20.0e-3f, 50.0e-3f, 100.0e-3f, 200.0e-3f, 500.0e-3f, 1.0f};

	uint16_t length = sizeof(list) / sizeof(float);

	index = (index + Direction + length) % length;

	yScale = list[index];

}

static void ChangeXOffset(int Direction)
{
	uint16_t wave_len;

	wave_len = WaveformCapture_GetBufferLength();

	xOffset += Direction * wave_len * 0.01; // 每次变化百分之1

	if(xOffset >= wave_len)
	{
		xOffset = wave_len - 1;
	}

	if(xOffset < 0)
	{
		xOffset = 0;
	}
}

