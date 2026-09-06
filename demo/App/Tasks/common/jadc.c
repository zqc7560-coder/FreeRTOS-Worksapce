/**
  ******************************************************************************
  * @文件  jadc.c
  * @作者  铁头山羊
  * @简介  ADC注入组相关代码的源文件。
  ******************************************************************************
  *
  ==============================================================================
                               ## JADC的特性 ##
  ==============================================================================

  (+) 使用FreeRTOS的邮箱传递结果，可保护数据的完整性

  (+) 使用定时器周期性触发ADC采集，实时更新数据

                                ## 使用方法 ##
  ==============================================================================

  (#) 在使用前请务必调用JADC_Init()方法进行初始化
  (#) 通过FreeRTOS的邮箱获取转换结果，代码如下

      extern QueueHandle_t xJADCMailBox; // 声明邮箱句柄
      JADC_ResultsTypeDef result = {0};

      xQueuePeek(xJADCMailBox, (void *)&result, 0); // 通过xQueuePeek方法接收结果

      DMMRangeTypeDef dmmRange = result.DMMRange; // 获取万用表的挡位
      float dmmValue = result.DMMValue;           // 获取万用表的值
      float regulator = result.RegulatorVoltage;  // 获取稳压电源的输出电压
      float triggerLevel = result.TriggerLevel;   // 获取示波器触发电压的大小

  ******************************************************************************
  */

/* 引用 -----------------------------------------------------------------------*/
#include "main.h"
#include "jadc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


/* 变量声明 ---------------------------------------------------------------------*/
QueueHandle_t xJADCMailBox; // ADC注入组结果邮箱

/* 私有函数声明 ------------------------------------------------------------------*/
static DMMRangeTypeDef GetDMMRange(void);
static float CalcDMMValue(uint16_t adcRaw, DMMRangeTypeDef range, float avdd);


/* 函数定义 ---------------------------------------------------------------------*/
/**
 * @简介：对ADC的注入组进行初始化
 */
void JADC_Init(void)
{
	/* 定时器2的句柄，由于变量声明在其它源文件中，故加extern关键字 */
	extern TIM_HandleTypeDef htim2;

	extern ADC_HandleTypeDef hadc1;

	/* 创建邮箱，该邮箱用于传递注入序列的结果 */
	xJADCMailBox = xQueueCreate(1, sizeof(JADC_ResultsTypeDef));

	/* 启动定时器2，该定时器用于ADC注入序列的触发 */
	HAL_TIM_Base_Start(&htim2);

	HAL_ADCEx_Calibration_Start(&hadc1);

	/* 以中断方式启动ADC的注入序列，注入序列的分配如下：
	 * jadc_ch1 - 采集稳压电源的运放输出端的电压
	 * jadc_ch2 - 采集万用表的放大器输出端的电压
	 * jadc_ch3 - 采集触发电压
	 * jadc_ch4 - 采集内部参考电压 Vref_internal */
	HAL_ADCEx_InjectedStart_IT(&hadc1);
}

JADC_ResultsTypeDef JADC_GetResult(void)
{
	JADC_ResultsTypeDef result = {0};
	extern QueueHandle_t xJADCMailBox; // JADC结果邮箱的句柄，在外部定义

	xQueuePeek(xJADCMailBox, &result, 0);

	return result;
}

JADC_ResultsTypeDef JADC_GetResultFromISR(BaseType_t *pxHigherPriorityTaskWoken)
{
	JADC_ResultsTypeDef result = {0};
	extern QueueHandle_t xJADCMailBox; // JADC结果邮箱的句柄，在外部定义

	xQueuePeekFromISR(xJADCMailBox, &result);

	return result;
}

/**
 * @简介：ADC注入组中断的回调函数
 */
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	extern ADC_HandleTypeDef hadc1;
	extern TaskHandle_t lcdTask;       // LCD任务的句柄，在外部定义
	extern QueueHandle_t xJADCMailBox; // JADC结果邮箱的句柄，在外部定义

	if(hadc->Instance == ADC1)
	{
		/* 读取注入序列1~4的原始值 */
		uint16_t jdr1 = HAL_ADCEx_InjectedGetValue(&hadc1, ADC_INJECTED_RANK_1);
		uint16_t jdr2 = HAL_ADCEx_InjectedGetValue(&hadc1, ADC_INJECTED_RANK_2);
		uint16_t jdr3 = HAL_ADCEx_InjectedGetValue(&hadc1, ADC_INJECTED_RANK_3);
		uint16_t jdr4 = HAL_ADCEx_InjectedGetValue(&hadc1, ADC_INJECTED_RANK_4);

		/* 使用单片机内置的Vref_internal(标称1.2V)计算模拟供电电压AVdd的实际值 */
		float avdd = 4095.0f / jdr4 * 1.2f;

		/* 获取万用表的量程挡位 */
		DMMRangeTypeDef dmmRange = GetDMMRange();

		/* 计算稳压电源的输出电压，放大电路的增益为1/13 */
		float regulator = jdr1 / 4095.0f * avdd * 13.0f;

		// result.RegulatorVoltage = result.RegulatorVoltage * 0.9848982f + 0.6316479f; // 修正

		/* 计算触发信号的电压值 */
		float trigger = jdr3 / 4095.0f * avdd * 2.0f - 2.5f;

		/* 计算dmm的值 */
		float dmm = CalcDMMValue(jdr2, dmmRange, avdd);

		/* 将结果写入到结构体当中 */
		JADC_ResultsTypeDef result = {0};

		result.AVdd = avdd;
		result.DMMRange = dmmRange;
		result.DMM = dmm;
		result.Regulator = regulator;
		result.Trigger = trigger;

		/* 向邮箱写入新结果 */
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;

		xQueueOverwriteFromISR(xJADCMailBox, (void *)&result, &xHigherPriorityTaskWoken);

		/* 使用任务通知触发显示器重绘 */
		xTaskNotifyFromISR(lcdTask/*xTaskToNotify*/, 0x00000018/*ulValue*/, eSetBits/*eAction*/, &xHigherPriorityTaskWoken);

		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}

/**
 * @简介：获取万用表模块的当前挡位
 */
static DMMRangeTypeDef GetDMMRange(void)
{
	if(HAL_GPIO_ReadPin(SW_DCV2_GPIO_Port, SW_DCV2_Pin) == GPIO_PIN_SET)
	{
		return DMMRange2V; /* 2V电压档 */
	}

	if(HAL_GPIO_ReadPin(SW_DCV10_GPIO_Port, SW_DCV10_Pin) == GPIO_PIN_SET)
	{
		return DMMRange10V; /* 10V电压档 */
	}

	if(HAL_GPIO_ReadPin(SW_DCV50_GPIO_Port, SW_DCV50_Pin) == GPIO_PIN_SET)
	{
		return DMMRange50V; /* 50V电压档 */
	}

	if(HAL_GPIO_ReadPin(SW_DCR10K_GPIO_Port, SW_DCR10K_Pin) == GPIO_PIN_SET)
	{
		return DMMRange10kOhmn; /* 10kΩ电阻档 */
	}

	if(HAL_GPIO_ReadPin(SW_DCR100K_GPIO_Port, SW_DCR100K_Pin) == GPIO_PIN_SET)
	{
		return DMMRange100kOhmn; /* 100kΩ电阻档 */
	}

	if(HAL_GPIO_ReadPin(SW_DCR1M_GPIO_Port, SW_DCR1M_Pin) == GPIO_PIN_SET)
	{
		return DMMRange1MOhmn; /* 1MΩ电阻档 */
	}

	return DMMRange1kOhmn; /* 1kΩ电阻档 */
}

/**
 * @简介：根据ADC采集的数据计算万用表的当前值
 * @参数：adcRaw - ADC采集的16位原始数据
 * @参数：range  - 万用表的当前挡位
 */
static float CalcDMMValue(uint16_t adcRaw, DMMRangeTypeDef range, float avdd)
{
	float volt = adcRaw / 4095.0f * avdd *2.0f - 2.0f;

	float R, Rx, R0, R1 = 1000000.0f;

	switch(range)
	{
		case DMMRange2V:
		{
			return volt;
		}
		case DMMRange10V:
		{
			return volt * 5.0f;
		}
		case DMMRange50V:
		{
			return volt * 25.0f;
		}
		case DMMRange1kOhmn:
		{
			R0 = 200.0f;

			R = volt/(2.5f-volt) * R0;
			Rx = R1*R / (R1 - R);

			return Rx;
		}
		case DMMRange10kOhmn:
		{
			R0 = 2000.0f;

			R = volt/(2.5f-volt) * R0;
			Rx = R1*R / (R1 - R);

			return Rx;
		}
		case DMMRange100kOhmn:
		{
			R0 = 20000.0f;

			R = volt/(2.5f-volt) * R0;
			Rx = R1*R / (R1 - R);

			return Rx;
		}
		case DMMRange1MOhmn:
		{
			R0 = 200000.0f;

			R = volt/(2.5f-volt) * R0;
			Rx = R1*R / (R1 - R);

			return Rx;
		}
		default:
			break;
	}

	return 0.0f;
}
