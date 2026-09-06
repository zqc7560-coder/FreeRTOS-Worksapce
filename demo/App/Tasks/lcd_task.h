/*
 * ui_task.h
 *
 *  Created on: Nov 21, 2025
 *      Author: liuyu
 */

#ifndef INC_LCD_TASK_H_
#define INC_LCD_TASK_H_

#include <stdint.h>

//
// 重绘任务通知比特位
//
#define WAVEFORM_REPAINT_BIT         0x00000001
#define CURSOR_LABEL_REPAINT_BIT     0x00000002
#define SCALE_LABEL_REPAINT_BIT      0x00000004
#define POWER_LABEL_REPAINT_BIT      0x00000008
#define DMM_LABEL_REPAINT_BIT        0x00000010
#define RUN_MODE_BANNER_REPAINT_BIT  0x00000020
#define SCALE_BANNER_REPAINT_BIT     0x00000040
#define CURSOR_BANNER_REPAINT_BIT    0x00000080
#define GENERATOR_BANNER_REPAINT_BIT 0x00000100
#define REPAINT_BIT_ALL              0x000001ff
#define ALL_BANNER_REPAINT_BIT       0x000001e0

void vLCDInit(void);
void vLCDTask(void *pvParameters);

#endif /* INC_LCD_TASK_H_ */
