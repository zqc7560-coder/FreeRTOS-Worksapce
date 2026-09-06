/**
  ******************************************************************************
  * @文件  waveform_capturer.h
  * @作者  铁头山羊
  * @简介  示波器模块的波形捕捉器，处理触发和波形采集。
  ******************************************************************************
  */

/* 防止头文件被递归引用而添加的宏 ----------------------------------------------------*/
#ifndef INC_WAVEFORM_CAPTURER_H_
#define INC_WAVEFORM_CAPTURER_H_

/* 引用 -----------------------------------------------------------------------*/
#include <stdint.h>
#include "FreeRTOS.h"
#include "timers.h"

/* 函数定义 ---------------------------------------------------------------------*/
/**
 * @简介：初始化波形捕捉器
 */
void WaveformCapture_Init(void);

/**
 * @简介：设置波形捕捉器的运行模式
 * @参数：Mode，模式。0 - 连续运行模式 1 - 单次模式
 */
void WaveformCapture_SetRunMode(uint8_t Mode);

/**
 * @简介：获取当前的运行模式
 * @返回：运行模式，0 - 连续运行模式 1 - 单次模式
 */
uint8_t WaveformCapture_GetRunMode(void);

/**
 * @简介：获取当前采样率
 * @返回：采样率的值，单位Hz
 */
float WaveformCapture_GetSampleRate(void);

/**
 * @简介：设置当前采样率
 * @参数：xScale - x轴缩放比例，单位s/div
 */
void WaveformCapture_SetSampleRateFromXScale(float xScale);

/**
 * @简介：获取波形缓冲区
 * @返回：波形缓冲区的指针
 */
const float *WaveformCapture_GetBuffer(void);

/**
 * @简介：获取波形缓冲区的长度
 * @返回：长度，单位点
 */
uint16_t WaveformCapture_GetBufferLength(void);

/**
 * @简介：“强制触发软件定时器”的回调函数
 */
void vForceTriggerTimerCallback(TimerHandle_t xTimer);

/**
 * @简介：“触发抑制软件定时器”的回调函数
 */
void vHoldOffTimerCallback(TimerHandle_t xTimer);

#endif /* INC_WAVEFORM_CAPTURER_H_ */
