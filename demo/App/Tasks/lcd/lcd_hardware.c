/*
 * lcd_hardware.c
 *
 *  Created on: Jan 13, 2026
 *      Author: liuyu
 */
#include "main.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "lcd.h"

static SemaphoreHandle_t m_semphr_dma_complete;
extern SPI_HandleTypeDef hspi1; // SPI接口，用于与屏幕通信

static void send_command(uint8_t Command);
static void send_data_dma(uint8_t *pData, uint16_t Size);
static void bk_light_control(uint8_t on);
static void reset(void);

void LCD_Hardware_Init(void)
{
	//
	// 为DMA创建信号量，该信号量用于等待DMA传输完成
	// 当DMA传输完成后会触发中断，在中断响应函数里给信号
	//
	m_semphr_dma_complete = xSemaphoreCreateBinary();

	//
	// 初始化LCD
	//
	LCD_InitTypeDef LCD_InitStruct;

	LCD_InitStruct.send_command_callback = send_command;
	LCD_InitStruct.send_data_callback = send_data_dma;
	LCD_InitStruct.back_light_control_callback = bk_light_control;
	LCD_InitStruct.reset_callback = reset;

	lcd_init(&LCD_InitStruct);
}

//
// @功能：命令发送回调函数，弱方法需要用户实现
// @参数：Command - 要发送的命令
// @参数：pData - 要发送的数据
// @参数：Size - 要发送数据的数量
//
static void send_command(uint8_t Command)
{
	HAL_GPIO_WritePin(LCD_NSS_GPIO_Port, LCD_NSS_Pin , GPIO_PIN_RESET); // 使能片选信号

	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET); // 切换到命令模式

	HAL_SPI_Transmit(&hspi1, &Command, 1, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(LCD_NSS_GPIO_Port, LCD_NSS_Pin , GPIO_PIN_SET); // 取消片选
}

static void send_data_dma(uint8_t *pData, uint16_t Size)
{
	HAL_GPIO_WritePin(LCD_NSS_GPIO_Port, LCD_NSS_Pin , GPIO_PIN_RESET); // 使能片选信号
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET); // 数据模式

	// 通过DMA发送数据
	HAL_SPI_Transmit_DMA(&hspi1, pData, Size);

	// 等待传输完成
	xSemaphoreTake(m_semphr_dma_complete, portMAX_DELAY);

	HAL_GPIO_WritePin(LCD_NSS_GPIO_Port, LCD_NSS_Pin , GPIO_PIN_SET); // 取消片选
}

//
// @功能：重写HAL库的SPI发送完成回调函数
//
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	if(hspi == &hspi1)
	{
		xSemaphoreGiveFromISR(m_semphr_dma_complete, &xHigherPriorityTaskWoken);
	}

	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

//
// @功能：控制LCD的背光
//
static void bk_light_control(uint8_t on)
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

static void reset(void)
{
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
	HAL_Delay(5);
}
