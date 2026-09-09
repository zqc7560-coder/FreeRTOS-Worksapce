/*
 * dmm_lable.c
 *
 *  Created on: Sep 8, 2026
 *      Author: 23224
 */

#include "dmm.h"
#include "lcd.h"

// DMM标签栏和显示DMM的数据
void DMMLabel_Repain(void)
{
	// 1.获取DMM的数据
	DMMData_t data = DMM_GetData();

	// 绘制浅灰色背景
	lcd_set_brush(0xcccccc);
	lcd_set_cursor(110, 215);
	lcd_fill_rect(120, 15);

	// 2.绘制数字万用表的挡位信息
	const char *rangeNames[] = {"DMM-50V:", "DMM-10V:", "DMM--2V:", "DMM--1k:", "DMM-10k:", "DMM100k:", "DMM--1M:"};
	lcd_set_cursor(116, 226);
	lcd_set_pen(0x000000);
	lcd_print_string(rangeNames[data.Range]);

	// 3.绘制万用表的具体数值
	const char *unitNames[] = {"V", "V", "V", "R", "R", "R", "R"};
	lcd_print_float_si(data.Value, 5, unitNames[data.Range]);
}
