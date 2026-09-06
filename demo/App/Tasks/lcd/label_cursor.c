/*
 * label_cursor.c
 *
 *  Created on: Feb 27, 2026
 *      Author: liuyu
 */
#include "lcd.h"
#include "color.h"
#include "waveform_capturer.h"
#include "lcd_task.h"
#include "panel_scale.h"
#include "panel_cursor.h"

//
// @功能：绘制游标标签
//
void RepaintCursorLabel(void)
{
	float cursorX1Val = lcd_get_x_cusor_value(GetCursorX1(), GetXScale());
	float cursorX2Val = lcd_get_x_cusor_value(GetCursorX2(), GetXScale());
	float cursorY1Val = lcd_get_y_cursor_value(GetCursorY1(), GetYScale());
	float cursorY2Val = lcd_get_y_cursor_value(GetCursorY2(), GetYScale());
	float deltaX = cursorX2Val - cursorX1Val;
	float deltaY = cursorY2Val - cursorY1Val;

	// 1号游标，深绿色
	lcd_set_cursor(8, 6);
	lcd_set_brush(CURSOR1_LABEL_COLOR);
	lcd_fill_rect(174,10);

	lcd_set_cursor(13, 15);
	lcd_set_pen(0x000000);
	lcd_print_string("x1:");
	lcd_print_float_si(cursorX1Val, 5, "s");

	lcd_set_cursor(99, 15);
	lcd_print_string("y1:");
	lcd_print_float_si(cursorY1Val, 5, "V");

	// 2号游标，铁锈色
	lcd_set_cursor(8, 21);
	lcd_set_brush(CURSOR2_LABEL_COLOR);
	lcd_fill_rect(174,10);

	lcd_set_cursor(13, 30);
	lcd_set_pen(0x000000);
	lcd_print_string("x2:");
	lcd_print_float_si(cursorX2Val, 5, "s");

	lcd_set_cursor(99, 30);
	lcd_print_string("y2:");
	lcd_print_float_si(cursorY2Val, 5, "V");

	// 绘制delta
	lcd_set_pen(0xff00ff);
	lcd_set_brush(0xffffff);

	lcd_set_cursor(8, 32);
	lcd_fill_rect(174, 10);

	lcd_set_cursor(34, 42);
	lcd_print_float_si(deltaX, 5, "s");

	lcd_set_cursor(120, 42);
	lcd_print_float_si(deltaY, 5, "V");
}
