/*
 * scale_panel.h
 *
 *  Created on: Feb 27, 2026
 *      Author: liuyu
 */

#ifndef LCD_PANEL_SCALE_H_
#define LCD_PANEL_SCALE_H_

void PanelScale_Repaint(void);
void PanelScale_Select(void);
void PanelScale_Deselect(void);
void PanelScale_UpDownKey(int Direction, int Repeat);

//
// @功能：获取X轴向缩放比
// @返回：X轴向缩放比，单位s/格
//
float GetXScale(void);

float GetYScale(void);

uint16_t GetXOffset(void);

#endif /* LCD_PANEL_SCALE_H_ */
