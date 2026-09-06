/*
 * lcd_task.c
 *
 *  Created on: Sep 5, 2026
 *      Author: 23224
 */

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "image1.h"
#include "image2.h"

static void BacklightControl(uint8_t on);
static void Reset(void);
static void SendCommand(uint8_t Cmd);
static void SendData(uint8_t *pData, uint16_t Size);
static void SetRowRange(uint16_t Start, uint16_t End);
static void SetColumnRange(uint16_t Start, uint16_t End);
static void ShowImage(const uint16_t pImage[], uint16_t Size);
static void ShowImage1(void);
static void ShowImage2(void);

void LCDTask_Init(void)
{
	BacklightControl(1);	//点亮背板4颗LED
	Reset();				//复位屏幕

	uint8_t dataToSend[10];

	SendCommand(0x11);	//退出休眠模式
	HAL_Delay(125);		//等待从睡眠模式中苏醒

	SendCommand(0x3a);	//0x3a 0x55 设置颜色传输格式为RGB565

	dataToSend[0] = 0x55;
	SendData(dataToSend, 1);

	SendCommand(0x29);	//0x29 开启屏幕显示


}

// @作用：LCD任务的任务代码
void vLCDTask(void *pvParameters)
{
	for(;;)
	{
		ShowImage1();
		vTaskDelay(pdMS_TO_TICKS(200));
		ShowImage2();
		vTaskDelay(pdMS_TO_TICKS(200));
	}
}

//
// @作用：控制LED的背光
// @参数：On 0-熄灭背光 1-点亮背光
//
static void BacklightControl(uint8_t on)
{
	if(on == 0)
	{
		HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_SET);
	}
}

//
// @作用：复位LCD
//
static void Reset(void)
{
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
	HAL_Delay(5);
}

//
//@作用：发送命令
//@参数：Cmd - 要发送的命令字节
//
static void SendCommand(uint8_t Cmd)
{
	extern SPI_HandleTypeDef hspi1;

	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_NSS_GPIO_Port, LCD_NSS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, &Cmd, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(LCD_NSS_GPIO_Port, LCD_NSS_Pin, GPIO_PIN_SET);
}

//
//@作用：发送数据
//@参数：pData - 要发送的数据
//@参数：Size - 数据的长度
//
static void SendData(uint8_t *pData, uint16_t Size)
{
	extern SPI_HandleTypeDef hspi1;

	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_NSS_GPIO_Port, LCD_NSS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, pData, Size, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(LCD_NSS_GPIO_Port, LCD_NSS_Pin, GPIO_PIN_SET);
}

//
// @作用：设置行范围
// @参数：Start - 起始行号
// @参数：End - 结束行号
//
static void SetRowRange(uint16_t Start, uint16_t End)
{
	uint8_t dataToSend[4];

	SendCommand(0x2b);	// 设置行命令

	dataToSend[0] = (Start >> 8) & 0xff;	//Start的高8位
	dataToSend[1] = Start & 0xff; 			//Start的低8位
	dataToSend[2] = (End >> 8) & 0xff;		//End的高8位
	dataToSend[3] = End & 0xff; 			//End的低8位

	SendData(dataToSend, 4);
}

//
// @作用：设置列范围
// @参数：Start - 起始列号
// @参数：End - 结束列号
//
static void SetColumnRange(uint16_t Start, uint16_t End)
{
	uint8_t dataToSend[4];

	SendCommand(0x2a);	// 设置列命令

	dataToSend[0] = (Start >> 8) & 0xff;	//Start的高8位
	dataToSend[1] = Start & 0xff; 			//Start的低8位
	dataToSend[2] = (End >> 8) & 0xff;		//End的高8位
	dataToSend[3] = End & 0xff; 			//End的低8位

	SendData(dataToSend, 4);
}

//
// @作用：显示图像
// @参数：pImage - 要显示的图像的数据
// @参数：Size - 图像的尺寸（像素点的数量）
//
static void ShowImage(const uint16_t pImage[], uint16_t Size)
{
	SendCommand(0x2c);
	SendData((uint8_t *)pImage, Size * 2);
}

// 显示图像1
static void ShowImage1(void)
{
	SetRowRange(80, 239);
	SetColumnRange(60, 179);
	ShowImage(image1, 160*120);
}

// 显示图像2
static void ShowImage2(void)
{
	SetRowRange(80, 239);
	SetColumnRange(60, 179);
	ShowImage(image2, 160*120);
}
