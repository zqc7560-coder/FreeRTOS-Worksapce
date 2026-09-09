/*
 * dmm.c
 *
 *  Created on: Sep 8, 2026
 *      Author: 23224
 */

#include "FreeRTOS.h"
#include "queue.h"
#include "dmm.h"

static QueueHandle_t xMailboxForDMM;

//
// @作用：对DMM数字万用表模块进行初始化
//
void DMM_Init(void)
{
	xMailboxForDMM = xQueueCreate(1, sizeof(DMMData_t));	// 创建邮箱

	// 编写虚拟测试值
	DMMData_t data = {.Range = 1, .Value = 4.9f};
	xQueueOverwrite(xMailboxForDMM, &data);
}

//
// @作用：获取DMM模块测量结果
// @返回值：DMM测量结果
//
DMMData_t DMM_GetData(void)
{
	DMMData_t data = {0};

	xQueuePeek(xMailboxForDMM, &data, 0);

	return data;
}
