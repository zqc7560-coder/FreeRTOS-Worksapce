/*
 * label_pwr.c
 *
 *  Created on: Feb 27, 2026
 *      Author: liuyu
 */
#include "lcd.h"
#include "jadc.h"

//
// @功能：绘制稳压电源标签
//
void RepaintPWRLabel(void)
{
	JADC_ResultsTypeDef jadcResult;

	jadcResult = JADC_GetResult();

	// 稳压电源
	lcd_set_cursor(6, 215);
	lcd_set_brush(0xcccccc);
	lcd_fill_rect(90,15);

	lcd_set_cursor(15, 227);
	lcd_set_pen(0x000000);
	lcd_print_string("Pwr:");
	lcd_print_float_si(jadcResult.Regulator, 5, "V");
}
