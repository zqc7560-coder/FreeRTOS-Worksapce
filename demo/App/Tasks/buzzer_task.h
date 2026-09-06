/*
 * buzzer_task.h
 *
 *  Created on: Mar 1, 2026
 *      Author: liuyu
 */

#ifndef BUZZER_TASK_H_
#define BUZZER_TASK_H_

void Buzzer_Init(void);
void vBuzzerTask(void *pvParameters);
void Buzzer_Beep(uint32_t Period);

#endif /* BUZZER_TASK_H_ */
