/*
 * waveform.c
 *
 *  Created on: Feb 27, 2026
 *      Author: liuyu
 */
#include "lcd.h"
#include "waveform_capturer.h"
#include "FreeRTOS.h"
#include "jadc.h"
#include "panel_scale.h"
#include "panel_cursor.h"

void RepaintWaveform(void)
{
	JADC_ResultsTypeDef jadcResult;

	jadcResult = JADC_GetResult();

	WaveformParamTypeDef waveformParams =
	{
		.Waveform = WaveformCapture_GetBuffer(),
		.WaveLength = WaveformCapture_GetBufferLength(),
		.XOffset = GetXOffset(),
		.XScale = GetXScale(),
		.YScale = GetYScale(),
		.SampleRate = WaveformCapture_GetSampleRate(),
		.CursorX1Pct = GetCursorX1(),
		.CursorY1Pct = GetCursorY1(),
		.CursorX2Pct = GetCursorX2(),
		.CursorY2Pct = GetCursorY2(),
		.Trigger  = jadcResult.Trigger,
	};

	// 绘制波形
	lcd_draw_waveform(&waveformParams);
}
