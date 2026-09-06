/*
 * cursor_panel.c
 *
 *  Created on: Feb 27, 2026
 *      Author: liuyu
 */
#include "lcd.h"
#include "color.h"
#include "lcd_task.h"
#include "panel_waveform.h"
#include "FreeRTOS.h"
#include "task.h"

#define SELECTED_INDEX_CURSOR_X1 0x00
#define SELECTED_INDEX_CURSOR_Y1 0x01
#define SELECTED_INDEX_CURSOR_X2 0x02
#define SELECTED_INDEX_CURSOR_Y2 0x03

static int8_t cursorX1 = 12; // 游标x1位置
static int8_t cursorY1 = 25; // 游标y1位置
static int8_t cursorX2 = 25; // 游标x2位置
static int8_t cursorY2 = -25; // 游标y2位置

static int8_t selectedIndex = -1; /* 当前选中的项目序号，负数代表未选中 */

static void MoveCursorX1(int Direction);
static void MoveCursorX2(int Direction);
static void MoveCursorY1(int Direction);
static void MoveCursorY2(int Direction);

void PanelCursor_Repaint(void)
{
	// banner，绿色
	lcd_set_cursor(260, 127);
	lcd_set_brush(PANNEL_BANNER_COLOR);
	lcd_fill_rect(60,15);

	// banner标题，橙色
	lcd_set_cursor(272, 140);
	lcd_set_pen(PANNEL_BANNER_TITLE_COLOR);
	lcd_print_string("Cursor");

	// 面板背景，灰色
	lcd_set_cursor(260, 142);
	lcd_set_brush(PANNEL_BACK_COLOR);
	lcd_fill_rect(60,35);

	lcd_set_pen(0x000000);

	// cursor_x1被选中，绘制选中标记
	if(selectedIndex == SELECTED_INDEX_CURSOR_X1)
	{
		lcd_set_brush(PANNEL_SELECTED_COLOR);
		lcd_set_cursor(271, 148);
		lcd_fill_rect(16, 10);
	}
	else
	{
		lcd_set_brush(PANNEL_BACK_COLOR);
	}

	lcd_set_cursor(272, 158);
	lcd_print_string("x1");

	// cursor_x2被选中，绘制选中标记
	if(selectedIndex == SELECTED_INDEX_CURSOR_X2)
	{
		lcd_set_brush(PANNEL_SELECTED_COLOR);
		lcd_set_cursor(292, 148);
		lcd_fill_rect(16, 10);
	}
	else
	{
		lcd_set_brush(PANNEL_BACK_COLOR);
	}

	lcd_set_cursor(293, 158);
	lcd_print_string("x2");

	// cursor_y1被选中，绘制选中标记
	if(selectedIndex == SELECTED_INDEX_CURSOR_Y1)
	{
		lcd_set_brush(PANNEL_SELECTED_COLOR);
		lcd_set_cursor(271, 161);
		lcd_fill_rect(16, 10);
	}
	else
	{
		lcd_set_brush(PANNEL_BACK_COLOR);
	}

	lcd_set_cursor(272, 171);
	lcd_print_string("y1");

	// cursor_y2被选中，绘制选中标记
	if(selectedIndex == SELECTED_INDEX_CURSOR_Y2)
	{
		lcd_set_brush(PANNEL_SELECTED_COLOR);
		lcd_set_cursor(292, 161);
		lcd_fill_rect(16, 10);
	}
	else
	{
		lcd_set_brush(PANNEL_BACK_COLOR);
	}

	lcd_set_cursor(293, 171);
	lcd_print_string("y2");
}

void PanelCursor_Select(void)
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
		if(selectedIndex >= 4)
		{
			selectedIndex -= 4;
		}
	}
}

void PanelCursor_Deselect(void)
{
	/* 通过设置一个负数表示当前未选中 */
	selectedIndex = -1;
}

void PanelCursor_UpDownKey(int Direction, int Repeat)
{
	extern TaskHandle_t lcdTask;

	if(selectedIndex < 0) return;

	/* 当前选中cursor_x1 */
	if(selectedIndex == SELECTED_INDEX_CURSOR_X1)
	{
		MoveCursorX1(-Direction);
	}
	/* 当前选中cursor_x2 */
	else if(selectedIndex == SELECTED_INDEX_CURSOR_X2)
	{
		MoveCursorX2(-Direction);
	}
	/* 当前选中cursor_y1 */
	else if(selectedIndex == SELECTED_INDEX_CURSOR_Y1)
	{
		MoveCursorY1(Direction);
	}
	/* 当前选中cursor_y2 */
	else if(selectedIndex == SELECTED_INDEX_CURSOR_Y2)
	{
		MoveCursorY2(Direction);
	}

	xTaskNotify(lcdTask, CURSOR_BANNER_REPAINT_BIT | WAVEFORM_REPAINT_BIT| CURSOR_LABEL_REPAINT_BIT, eSetBits);
}

int8_t GetCursorX1(void)
{
	return cursorX1;
}

int8_t GetCursorX2(void)
{
	return cursorX2;
}

int8_t GetCursorY1(void)
{
	return cursorY1;
}

int8_t GetCursorY2(void)
{
	return cursorY2;
}

static void MoveCursorX1(int Direction)
{
	cursorX1 = cursorX1 + Direction;

	if(cursorX1 <   0) { cursorX1 =   0; }
	if(cursorX1 > 100) { cursorX1 = 100; }
}

static void MoveCursorX2(int Direction)
{
	cursorX2 = cursorX2 + Direction;

	if(cursorX2 <   0) { cursorX2 =   0; }
	if(cursorX2 > 100) { cursorX2 = 100; }
}
static void MoveCursorY1(int Direction)
{
	cursorY1 = cursorY1 + Direction;

	if(cursorY1 <-100) { cursorY1 =-100; }
	if(cursorY1 > 100) { cursorY1 = 100; }
}
static void MoveCursorY2(int Direction)
{
	cursorY2 = cursorY2 + Direction;

	if(cursorY2 <-100) { cursorY2 =-100; }
	if(cursorY2 > 100) { cursorY2 = 100; }
}

