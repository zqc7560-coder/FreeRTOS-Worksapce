/*
 * RunModePanel.h
 *
 *  Created on: Feb 27, 2026
 *      Author: liuyu
 */

#ifndef LCD_PANEL_RUN_MODE_H_
#define LCD_PANEL_RUN_MODE_H_

void PanelRunMode_Repaint(void);
void PanelRunMode_Select(void);
void PanelRunMode_Deselect(void);
void PanelRunMode_UpDownKey(int Direction, int Repeat);

#endif /* LCD_PANEL_RUN_MODE_H_ */
