/**
  ******************************************************************************
  * @文件  jadc.h
  * @作者  铁头山羊
  * @简介  ADC注入组相关代码的头文件。
  ******************************************************************************
  */

/* 防止头文件被递归引用而添加的宏 ----------------------------------------------------*/
#ifndef INC_JADC_H_
#define INC_JADC_H_

/* 引用 -----------------------------------------------------------------------*/
#include "FreeRTOS.h"

/* 数据类型定义 -----------------------------------------------------------------*/
/**
  * @简介：表示万用表挡位的枚举类型
  */
typedef enum
{
	DMMRange2V,       /* 万用表2V电压档     */
	DMMRange10V,      /* 万用表10V电压档    */
	DMMRange50V,      /* 万用表50V电压档    */
	DMMRange1kOhmn,   /* 万用表1k欧姆电阻档  */
	DMMRange10kOhmn,  /* 万用表10k欧姆电阻档 */
	DMMRange100kOhmn, /* 万用表100k欧姆电阻档*/
	DMMRange1MOhmn,   /* 万用表1M欧姆电阻档  */
} DMMRangeTypeDef;

/**
 * @简介：存储ADC注入序列采集结果的结构体类型
 */
typedef struct
{
	DMMRangeTypeDef DMMRange; /* 万用表的当前挡位，取值范围参照@ref  DMMRangeTypeDef*/
	float DMM;           /* 万用表的值，单位可以取V或者Ω，挡位不同含义不同 */
	float Regulator;   /* 稳压电源的输出电压，单位V */
	float Trigger;       /* 触发电压的大小，单位V */
	float AVdd;
}JADC_ResultsTypeDef;

/* 函数定义 ---------------------------------------------------------------------*/
/**
 * @简介：对ADC注入序列的采集工作做初始化
 */
void JADC_Init(void);
JADC_ResultsTypeDef JADC_GetResult(void);
JADC_ResultsTypeDef JADC_GetResultFromISR(BaseType_t *pxHigherPriorityTaskWoken);

#endif /* INC_JADC_H_ */
