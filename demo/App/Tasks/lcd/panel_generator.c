/*
 * panel_generator.c
 *
 *  Created on: Feb 27, 2026
 *      Author: liuyu
 */
#include "lcd_task.h"
#include "color.h"
#include "lcd.h"
#include "waveform_generator.h"
#include "FreeRTOS.h"
#include "task.h"

#define SELECTED_INDEX_SHAPE 0x00
#define SELECTED_INDEX_FREQ  0x01

static int8_t selectedIndex = -1; /* 当前选中的项目序号，负数代表未选中 */

static const char *GetWaveformName(void);

void PanelGenerator_Repaint(void)
{
	// banner，绿色
	lcd_set_cursor(260, 184);
	lcd_set_brush(PANNEL_BANNER_COLOR);
	lcd_fill_rect(60,15);

	// banner标题，橙色
	lcd_set_cursor(262, 197);
	lcd_set_pen(PANNEL_BANNER_TITLE_COLOR);
	lcd_print_string("Generato");

	// 面板背景，灰色
	lcd_set_cursor(260, 199);
	lcd_set_brush(PANNEL_BACK_COLOR);
	lcd_fill_rect(60,35);

	lcd_set_pen(0x000000);

	// 绘制波形类型选项
	if(selectedIndex == SELECTED_INDEX_SHAPE)
	{
		lcd_set_brush(PANNEL_SELECTED_COLOR);
		lcd_set_cursor(262, 202);
		lcd_fill_rect(58, 10);
	}
	else
	{
		lcd_set_brush(PANNEL_BACK_COLOR);
	}

	lcd_set_cursor(263, 212);

	// 绘制波形类型字符串
	lcd_print_string(GetWaveformName());

	// 绘制频率选项
	if(selectedIndex == SELECTED_INDEX_FREQ)
	{
		lcd_set_brush(PANNEL_SELECTED_COLOR);
		lcd_set_cursor(262, 212);
		lcd_fill_rect(58, 10);
	}
	else
	{
		lcd_set_brush(PANNEL_BACK_COLOR);
	}

	lcd_set_cursor(263, 222);
	lcd_print_float_si(WaveformGenerator_GetFrequency(), 6, "Hz");
}

void PanelGenerator_Select(void)
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
		if(selectedIndex >= 2)
		{
			selectedIndex -= 2;
		}
	}
}

void PanelGenerator_Deselect(void)
{
	/* 通过设置一个负数表示当前未选中 */
	selectedIndex = -1;
}

void PanelGenerator_UpDownKey(int Direction, int Repeat)
{
	extern TaskHandle_t lcdTask;

	if(selectedIndex < 0) return;

	/* 按Up/Down更改波形类型 */
	if(selectedIndex == SELECTED_INDEX_SHAPE) // 发生器面板，波形类型
	{
		uint8_t waveform;

		waveform = WaveformGenerator_GetWaveform();

		/* 根据按钮方向递增或者递减波形类型的序号 */
		waveform = (waveform + 4 - Direction) % 4;

		/* 设置新的波形类型 */
		WaveformGenerator_SetWaveform(waveform);
	}
	/* 按Up/Down调节信号源频率 */
	else if(selectedIndex == SELECTED_INDEX_FREQ) // 发生器面板，频率
	{
		/* 当前频率在列表中的序号 */
		static uint8_t freqIndex = 6; // 初始序号选择6，对应1kHz

		/* 频率列表 */
		static const float freqList[] = {10.0f, 20.0f, 50.0f, 100.0f, 200.0f, 500.0f, 1000.0f, 2.0e3f, 5.0e3f, 10.0e3f, 20.0e3f, 50.0e3f};

		/* 计算频率列表的长度 */
		uint16_t numOfFreqs = sizeof(freqList) / sizeof(float);

		/* 根据按键方向调节频率 */
		freqIndex = (freqIndex + numOfFreqs + Direction) % numOfFreqs;

		/* 设置新的频率 */
		WaveformGenerator_SetFrequency(freqList[freqIndex]);
	}

	/* 通知LCD任务重绘信号发生器面板 */
	xTaskNotify(lcdTask, GENERATOR_BANNER_REPAINT_BIT, eSetBits);
}

/**
 * @简介：获取当前波形类型对应的字符串名称
 */
static const char *GetWaveformName(void)
{
	const char *ret = "Invalid";

	uint8_t waveform = WaveformGenerator_GetWaveform();

	if(waveform == WAVEFORM_TYPE_OFF)
	{
		ret = "OFF";
	}
	else if(waveform == WAVEFORM_TYPE_SIN)
	{
		ret = "Sin";
	}
	else if(waveform == WAVEFORM_TYPE_TRIANGLE)
	{
		ret = "Triangle";
	}
	else if(waveform == WAVEFORM_TYPE_SQUARE)
	{
		ret = "Square";
	}

	return ret;
}

