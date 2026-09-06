/**
  ******************************************************************************
  * @文件  waveform_generator.h
  * @作者  铁头山羊
  * @简介  波形发生器的头文件。
  ******************************************************************************
  */

/* 防止头文件被递归引用而添加的宏 ----------------------------------------------------*/
#ifndef INC_WAVEFORM_GENERATOR_H_
#define INC_WAVEFORM_GENERATOR_H_

/* 引用 -----------------------------------------------------------------------*/
#include <stdint.h>

/* 宏定义 ----------------------------------------------------------------------*/
#define WAVEFORM_TYPE_OFF      0x00 // 关闭
#define WAVEFORM_TYPE_SIN      0x01 // 正弦波
#define WAVEFORM_TYPE_TRIANGLE 0x02 // 三角波
#define WAVEFORM_TYPE_SQUARE   0x03 // 方波

/* 函数定义 ---------------------------------------------------------------------*/
/**
 * @简介：初始化波形发生器
 */
void WaveformGenerator_Init(void);

/**
 * @简介：设置波形类型
 * @参数：WaveformType，波形类型：
 *         WAVEFORM_TYPE_OFF - 关闭波形输出
 *         WAVEFORM_TYPE_SIN - 正弦波
 *         WAVEFORM_TYPE_TRIANGLE - 三角波
 *         WAVEFORM_TYPE_SQUARE - 方波
 */
void WaveformGenerator_SetWaveform(uint8_t WaveformType);

/**
 * @简介：获取当前波形类型
 * @返回： WAVEFORM_TYPE_OFF - 关闭波形输出
 *       WAVEFORM_TYPE_SIN - 正弦波
 *       WAVEFORM_TYPE_TRIANGLE - 三角波
 *       WAVEFORM_TYPE_SQUARE - 方波
 */
uint8_t WaveformGenerator_GetWaveform(void);

/**
 * @简介：设置波形发生器的频率
 * @参数：freq - 频率，单位Hz
 */
void WaveformGenerator_SetFrequency(float freq);

/**
 * @简介：获取波形发生器的频率
 * @返回：当前频率，单位Hz
 */
float WaveformGenerator_GetFrequency(void);

#endif /* INC_WAVEFORM_GENERATOR_H_ */
