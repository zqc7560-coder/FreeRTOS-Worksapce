/*
 * lcd_task.c
 *
 *  Created on: Nov 21, 2025
 *      Author: liuyu
 */

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "lcd_task.h"
#include "lcd.h"
#include "panel_run_mode.h"
#include "panel_scale.h"
#include "panel_cursor.h"
#include "panel_generator.h"
#include "panel_waveform.h"
#include "label_pwr.h"
#include "label_dmm.h"
#include "lcd_hardware.h"
#include "color.h"
#include "waveform_capturer.h"

void run_admin_server(void);

void vLCDInit(void)
{
	LCD_Hardware_Init();
}

//
// @功能：LCD任务函数，负责屏幕绘制
//
void vLCDTask(void *pvParameters)
{
	extern TaskHandle_t lcdTask;

	// 第一次运行此任务时需要绘制所有部件，因此需要设置该任务通知的所有比特位
	// 每个比特位代表一个UI部件
	// 初始状态下需要绘制所有UI部件
	xTaskNotify(lcdTask, REPAINT_BIT_ALL, eSetBits);

	//
	// 清空显示器
	//
	lcd_set_brush(SCREEN_BACK_COLOR);
	lcd_clear();

	for(;;)
	{
		uint32_t ulNotifycationValue;

		// 等待任务通知
		xTaskNotifyWait(0x00000000 /*ulBitsToClearOnEntry*/,
				        REPAINT_BIT_ALL /*ulBitsToClearOnExit*/,
					    &ulNotifycationValue /*pulNotificationValue*/,
					    portMAX_DELAY /*xTicksToWait*/);

		// 重绘波形显示区
		if(ulNotifycationValue & WAVEFORM_REPAINT_BIT)
		{
			RepaintWaveform();
		}

		// 重绘游标标签
		if(ulNotifycationValue & CURSOR_LABEL_REPAINT_BIT)
		{
			RepaintCursorLabel();
		}

		// 重绘比例因子标签
		if(ulNotifycationValue & SCALE_LABEL_REPAINT_BIT)
		{
			RepaintScaleLable();
		}

		// 重绘电源电压标签
		if(ulNotifycationValue & POWER_LABEL_REPAINT_BIT)
		{
			RepaintPWRLabel();
		}

		// 重绘万用表标签
		if(ulNotifycationValue & DMM_LABEL_REPAINT_BIT)
		{
			RepaintDMMLabel();
		}

		// 绘制运行模式面板
		if(ulNotifycationValue & RUN_MODE_BANNER_REPAINT_BIT)
		{
			PanelRunMode_Repaint();
		}

		// 绘制缩放面板
		if(ulNotifycationValue & SCALE_BANNER_REPAINT_BIT)
		{
			PanelScale_Repaint();
		}

		// 绘制游标面板
		if(ulNotifycationValue & CURSOR_BANNER_REPAINT_BIT)
		{
			PanelCursor_Repaint();
		}

		// 绘制信号发生器面板
		if(ulNotifycationValue & GENERATOR_BANNER_REPAINT_BIT)
		{
			PanelGenerator_Repaint();
		}
	}
}
