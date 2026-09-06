/*
 * buzzer_task.h
 *
 *  Created on: Sep 5, 2026
 *      Author: 23224
 */

#ifndef TASK_BUZZER_TASK_H_
#define TASK_BUZZER_TASK_H_

void Buzzer_Init();
void vBuzzerTask(void *pvParameters);
void Buzzer_Beep();

#endif /* TASK_BUZZER_TASK_H_ */
