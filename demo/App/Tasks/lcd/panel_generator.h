/*
 * panel_generator.h
 *
 *  Created on: Feb 27, 2026
 *      Author: liuyu
 */

#ifndef LCD_PANEL_GENERATOR_H_
#define LCD_PANEL_GENERATOR_H_

void PanelGenerator_Repaint(void);
void PanelGenerator_Select(void);
void PanelGenerator_Deselect(void);
void PanelGenerator_UpDownKey(int Direction, int Repeat);

#endif /* LCD_PANEL_GENERATOR_H_ */
