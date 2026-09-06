/*
 * label_dmm.c
 *
 *  Created on: Feb 27, 2026
 *      Author: liuyu
 */
#include "lcd.h"
#include "lcd_task.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "jadc.h"

//
// @功能：绘制万用表标签
//
void RepaintDMMLabel(void)
{
	JADC_ResultsTypeDef jadcResult;

	lcd_set_cursor(110, 215);
	lcd_set_brush(0xcccccc);
	lcd_fill_rect(122,15);

	lcd_set_cursor(118, 228);
	lcd_set_pen(0x000000);
	lcd_print_string("DMM");

	jadcResult = JADC_GetResult();

	switch(jadcResult.DMMRange)
	{
		case 0:
			lcd_print_string("--2V:");
			lcd_print_float_si(jadcResult.DMM, 6, "V");
			break;
		case 1:
			lcd_print_string("-10V:");
			lcd_print_float_si(jadcResult.DMM, 6, "V");
			break;
		case 2:
			lcd_print_string("-50V:");
			lcd_print_float_si(jadcResult.DMM, 6, "V");
			break;
		case 3:
			lcd_print_string("--1k:");
			lcd_print_float_si(jadcResult.DMM, 6, "R");
			break;
		case 4:
			lcd_print_string("-10k:");
			lcd_print_float_si(jadcResult.DMM, 6, "R");
			break;
		case 5:
			lcd_print_string("100k:");
			lcd_print_float_si(jadcResult.DMM, 6, "R");
			break;
		case 6:
			lcd_print_string("--1M:");
			lcd_print_float_si(jadcResult.DMM, 6, "R");
			break;
		default: break;
	}
}

