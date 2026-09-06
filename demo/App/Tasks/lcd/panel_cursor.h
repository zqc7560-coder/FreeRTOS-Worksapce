/*
 * cursor_panel.h
 *
 *  Created on: Feb 27, 2026
 *      Author: liuyu
 */

#ifndef LCD_PANEL_CURSOR_H_
#define LCD_PANEL_CURSOR_H_

void PanelCursor_Repaint(void);
void PanelCursor_Select(void);
void PanelCursor_Deselect(void);
void PanelCursor_UpDownKey(int Direction, int Repeat);

int8_t GetCursorX1(void);
int8_t GetCursorX2(void);
int8_t GetCursorY1(void);
int8_t GetCursorY2(void);

#endif /* LCD_PANEL_CURSOR_H_ */
