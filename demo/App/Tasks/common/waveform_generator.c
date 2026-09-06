/*
 * waveform_generator.c
 *
 *  Created on: Dec 1, 2025
 *      Author: liuyu
 */
#include "main.h"
#include "waveform_generator.h"
#include "jadc.h"
#include <math.h>

static uint8_t waveform; /* 参数，波形类型 */
static float frequency;  /* 参数，波形频率 */
static uint16_t buffer[1000]; /* 波形缓冲区 */
static volatile uint16_t waveform_length; /* 波形数据的实际长度，buffer并不会被完全使用，数据长度是动态计算的 */

static void ReloadWaveform(void);

/**
 * @简介：初始化波形发生器
 */
void WaveformGenerator_Init(void)
{
	/* 初始状态下关闭波形发生器 */
	waveform = WAVEFORM_TYPE_OFF;

	/* 初始频率为1kHz */
	frequency = 1000.0f;

	/* 重新加载波形 */
	ReloadWaveform();
}

/**
 * @简介：设置波形类型
 * @参数：WaveformType，波形类型：
 *         WAVEFORM_TYPE_OFF - 关闭波形输出
 *         WAVEFORM_TYPE_SIN - 正弦波
 *         WAVEFORM_TYPE_TRIANGLE - 三角波
 *         WAVEFORM_TYPE_SQUARE - 方波
 */
void WaveformGenerator_SetWaveform(uint8_t WaveformType)
{
	/* 设置波形类型 */
	waveform = WaveformType;

	/* 重新加载波形 */
	ReloadWaveform();
}

/**
 * @简介：获取当前波形类型
 * @返回： WAVEFORM_TYPE_OFF - 关闭波形输出
 *       WAVEFORM_TYPE_SIN - 正弦波
 *       WAVEFORM_TYPE_TRIANGLE - 三角波
 *       WAVEFORM_TYPE_SQUARE - 方波
 */
uint8_t WaveformGenerator_GetWaveform(void)
{
	return waveform;
}

/**
 * @简介：设置波形发生器的频率
 * @参数：freq - 频率，单位Hz
 */
void WaveformGenerator_SetFrequency(float freq)
{
	/* 设置新频率 */
	frequency = freq;

	/* 重新加载波形 */
	ReloadWaveform();
}

/**
 * @简介：获取波形发生器的频率
 * @返回：当前频率，单位Hz
 */
float WaveformGenerator_GetFrequency(void)
{
	return frequency;
}

/**
 * @简介：根据设置的参数重新加载波形
 */
static void ReloadWaveform(void)
{
	extern DAC_HandleTypeDef hdac;  // DAC的句柄
	extern TIM_HandleTypeDef htim5; // 定时器5的句柄，定时器5负责触发DAC转换

	/* 暂停DAC的波形输出 */
	HAL_TIM_Base_Stop(&htim5); // 关闭定时器
	HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1);

	/* 根据波形频率计算定时器触发间隔，进而计算tim5的arr的值 */
	/* 原则是让buffer被尽量充分地利用 */
	uint16_t arr;
	if(frequency >= 500.0f) // 最高采样率500kHz
	{
		waveform_length = 500.0e3f / frequency;
		arr = 1;
	}
	else
	{
		waveform_length = 1000;
		arr = 1.0e6 / frequency / 1000 - 1;
	}

	/* 将计算得到的ARR的值设置进定时器 */
	__HAL_TIM_SET_AUTORELOAD(&htim5, arr);

	// 计算波形
	// 无波形，即直接输出低电压，此时输出电压大小应该是1.5V（中间电位）
	if(waveform == WAVEFORM_TYPE_OFF)
	{
		for(uint16_t i=0;i<waveform_length;i++)
		{
			buffer[i] = 1241; // 1.5V -> 4095/3.3*1.5 = 1,861.3636
		}
	}
	// 正弦波
	// 正弦波的中心电位1.5V，峰值0.8V
	else if(waveform == WAVEFORM_TYPE_SIN)
	{
		for(uint16_t i=0;i<waveform_length;i++)
		{
			buffer[i] = (sinf(6.2831853f*i/waveform_length)*0.9f + 1.0f)/3.3f*4095;
		}
	}
	/* 三角波 */
	else if(waveform == WAVEFORM_TYPE_TRIANGLE) // 三角波
	{
		for(uint16_t i=0;i<waveform_length;i++)
		{
			buffer[i] = 2.0f*i/waveform_length/3.3f*4095;
		}
	}
	/* 方波 */
	else if(waveform == WAVEFORM_TYPE_SQUARE) // 方波
	{
		for(uint16_t i=0;i<waveform_length;i++)
		{
			if(i < waveform_length/2)
			{
				buffer[i] = 2.0f / 3.3f * 4095;
			}
			else
			{
				buffer[i] = 0;
			}
		}
	}

	/* 重新启动DAC波形输出 */
	HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t *)buffer, waveform_length, DAC_ALIGN_12B_R);
	HAL_TIM_Base_Start(&htim5);

	/* 如果有波形输出则点亮指示灯 */
	if(waveform != WAVEFORM_TYPE_OFF)
	{
		HAL_GPIO_WritePin(AWG_LED_GPIO_Port, AWG_LED_Pin, GPIO_PIN_SET);
	}
}
