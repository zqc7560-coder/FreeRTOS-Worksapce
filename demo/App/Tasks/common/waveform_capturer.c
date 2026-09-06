/**
  ******************************************************************************
  * @文件  button.c
  * @作者  铁头山羊
  * @简介  适用于FreeRTOS的按钮驱动的源文件。
  ******************************************************************************
  *
  */

#include "jadc.h"
#include "waveform_capturer.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "stm32f1xx_hal.h"
#include "math.h"
#include "semphr.h"
#include "panel_scale.h"

#define BUFFER_LENGTH 1024    /* 波形存储缓冲区的长度 */

SemaphoreHandle_t xWaveformMutex; // 用于保护波形数组资源
static TimerHandle_t xForceTriggerTimer;
static TimerHandle_t xHoldOffTimer;

static uint8_t run_mode = 0; // 运行模式，0 - 连续运行模式 1 - 单次模式
static float sampleRate = 10000; // 采样率，默认10kHz
static uint16_t rawDataBuffer[BUFFER_LENGTH];
static float waveformBuffer[BUFFER_LENGTH]; // 示波器波形

/**
 * @简介：初始化波形捕捉器
 */
void WaveformCapture_Init(void)
{
	// 计算采样率
	WaveformCapture_SetSampleRateFromXScale(GetXScale());

	extern TIM_HandleTypeDef htim3;

	/* 启动定时器. 该定时器用于ADC规则序列的定时触发 */
	HAL_TIM_Base_Start(&htim3);

	/* 强制触发软件定时器 */
	/* 该定时器用于波形捕捉器的强制触发 */
	xForceTriggerTimer = xTimerCreate("Force Trigger Timer", pdMS_TO_TICKS(100), pdTRUE, NULL, vForceTriggerTimerCallback);

	/* 触发抑制软件定时器 */
	/* 该定时器通过设置触发抑制区间，防止高频信号或干扰信号导致的过快触发 */
	xHoldOffTimer = xTimerCreate("Hold Off Timer", pdMS_TO_TICKS(10), pdFALSE, NULL, vHoldOffTimerCallback);

	/* 互斥锁，用于波形缓冲区保护 */
	xWaveformMutex = xSemaphoreCreateMutex();

	/* 启动强制触发定时器 */
	xTimerChangePeriod(xForceTriggerTimer, pdMS_TO_TICKS(100), portMAX_DELAY);
}

/**
 * @简介：设置波形捕捉器的运行模式
 * @参数：Mode，模式。0 - 连续运行模式 1 - 单次模式
 */
void WaveformCapture_SetRunMode(uint8_t Mode)
{
	HAL_NVIC_DisableIRQ(EXTI3_IRQn);

	run_mode = Mode;

	HAL_NVIC_EnableIRQ(EXTI3_IRQn);
}

/**
 * @简介：获取当前的运行模式
 * @返回：运行模式，0 - 连续运行模式 1 - 单次模式
 */
uint8_t WaveformCapture_GetRunMode(void)
{
	return run_mode;
}

/**
 * @简介：获取波形缓冲区
 * @返回：波形缓冲区的指针
 */
const float *WaveformCapture_GetBuffer(void)
{
	return waveformBuffer;
}

/**
 * @简介：获取波形缓冲区的长度
 * @返回：长度，单位点
 */
uint16_t WaveformCapture_GetBufferLength(void)
{
	return BUFFER_LENGTH;
}

/**
 * @简介：获取当前采样率
 * @返回：采样率的值，单位Hz
 */
float WaveformCapture_GetSampleRate(void)
{
	return sampleRate + 0.5f;
}

/**
 * @简介：根据x轴缩放比例设置当前采样率
 * @参数：xScale - x轴缩放比例，单位s/div
 */
void WaveformCapture_SetSampleRateFromXScale(float xScale)
{
	sampleRate = BUFFER_LENGTH / (xScale * 8 * 2);

	if(sampleRate > 0.5e6f)
	{
		sampleRate = 0.5e6f;
	}
}

//
// @功能：重写EXTI中断回调函数
//
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	extern TIM_HandleTypeDef htim3;
	extern ADC_HandleTypeDef hadc1;

	if(GPIO_Pin == GPIO_PIN_3)
	{
		/* 关掉EXTI3的中断，这是为了实现触发抑制 */
		/* 后续将由xHoldOffTimer的回调函数再次把EXTI3的中断打开 */
		HAL_NVIC_DisableIRQ(EXTI3_IRQn);

		/* 根据采样率动态设置定时器的溢出周期 */
		__HAL_TIM_SET_AUTORELOAD(&htim3, round(12.0e6f/sampleRate) - 1);

		/* 开启DMA准备接收数据 */
		HAL_ADC_Start_DMA(&hadc1, (uint32_t *)rawDataBuffer, BUFFER_LENGTH);

		/* 启动强制触发定时器 */
		/* 如果一段时间后没有收到触发信号，则由此定时器强制触发 */
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		xTimerResetFromISR(xForceTriggerTimer, &xHigherPriorityTaskWoken);

		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}

//
// @功能：重写ADC常规序列转换结束的回调函数
//
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	extern ADC_HandleTypeDef hadc1;
	extern TaskHandle_t lcdTask;

	if(hadc == &hadc1)
	{
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		BaseType_t xResult;

		// 1. 尝试获取锁
		xResult = xSemaphoreTakeFromISR(xWaveformMutex, &xHigherPriorityTaskWoken);

		// 只有成功获取锁才能进行数据搬运
		// 如果未获取到锁就将数据丢弃
		if(xResult == pdTRUE)
		{
			JADC_ResultsTypeDef jadcResult;

			jadcResult = JADC_GetResultFromISR(&xHigherPriorityTaskWoken);

			// 2. 将数据转换并复制到另一个缓冲区waveform
			for(uint16_t i=0; i<BUFFER_LENGTH; i++)
			{
				waveformBuffer[i] = rawDataBuffer[i] / 4095.0f * jadcResult.AVdd * 2.0f - 2.5f;
			}
			// 3. 释放锁
			xSemaphoreGiveFromISR(xWaveformMutex, &xHigherPriorityTaskWoken);

			// 4. 触发重绘，只重绘波形区即可
			xTaskNotifyFromISR(lcdTask/*xTaskToNotify*/, 0x00000001/*ulValue*/, eSetBits/*eAction*/, &xHigherPriorityTaskWoken);
		}

		// 启动禁止触发定时器，到时间后再次打开中断
		xTimerStartFromISR(xHoldOffTimer, &xHigherPriorityTaskWoken);

		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}

/**
 * @简介：“强制触发软件定时器”的回调函数
 */
void vForceTriggerTimerCallback(TimerHandle_t xTimer)
{
	extern ADC_HandleTypeDef hadc1;

	/* 运行模式（Running Mode） */
	/* 仅运行模式下才能进行强制触发 */
	if(run_mode == 0)
	{
		/* 使用软件方式强制触发EXTI3中断 */
		__HAL_GPIO_EXTI_GENERATE_SWIT(GPIO_PIN_3);
	}
}

/**
 * @简介：“触发抑制软件定时器”的回调函数
 */
void vHoldOffTimerCallback(TimerHandle_t xTimer)
{
	if(run_mode == 0){
		// 清除期间触发的中断
		__HAL_GPIO_EXTI_CLEAR_FLAG(GPIO_PIN_3);
		HAL_NVIC_ClearPendingIRQ(EXTI3_IRQn);
		// 开启中断
		HAL_NVIC_EnableIRQ(EXTI3_IRQn);
	}
}
