/*
 * label_scale.c
 *
 *  Created on: Feb 27, 2026
 *      Author: liuyu
 */
#include "lcd.h"
#include "panel_scale.h"

//
// @功能：绘制缩放标签
//
void RepaintScaleLable(void)
{
	// dev，暗黄色
	lcd_set_cursor(187, 6);
	lcd_set_brush(0xdaa400);
	lcd_fill_rect(60,25);

	lcd_set_cursor(195, 18);
	lcd_set_pen(0x000000);
	lcd_print_float_si(GetXScale(), 5, "s");

	lcd_set_cursor(195, 29);
	lcd_print_float_si(GetYScale(), 5, "V");
}
