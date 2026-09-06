/**
  ******************************************************************************
  * @文件  button.c
  * @作者  铁头山羊
  * @简介  适用于FreeRTOS的按钮驱动的源文件。
  ******************************************************************************
  *
  ==============================================================================
                              ## 按钮驱动的特性 ##
  ==============================================================================

  (+) 不依赖底层硬件，可以被移植到各种硬件平台

  (+) 支持按钮的单击、长按和长按重复触发

  (+) 可由用户自定义长按触发最小时间，和长按重复触发间隔

                                ## 使用方法 ##
  ==============================================================================

  (#) 注意！按钮的IO引脚一定要设置为输入上拉。如果IO无内置上拉电阻，则需要外接。外接的上拉电阻阻值取10k欧
      姆左右。

  (#) 为按钮声明Button_TypeDef类型的全局变量，如果有多个需要为每个按钮声明一个变量。比如假设项目里有3个
      按钮，那么应该编写如下代码：

         Button_TypeDef button1, button2, button3;

  (#) 定义按钮动作触发时的回调函数，比如如下代码展示了按下按钮后切换LED亮灭状态的代码

         void OnButtonPressed(void)
         {
             toggle_led_state();
         }

  (#) 声明Button_InitTypeDef类型的变量，并填写初始化参数和回调函数。代码如下：

         Button_InitTypeDef Button_InitStruct = {0};

         Button_InitStruct.LongPressTime = ...;
         Button_InitStruct.PressCallback = OnButtonPressed;
         ...

         Button_Init(&button1, &Button_InitStruct);
         ...
         Button_Init(&button2, &Button_InitStruct);
         ...
         Button_Init(&button3, &Button_InitStruct);

  (#) 以一定间隔反复调用Button_Scan()函数。例如，可以把Button_Scan函数放到while循环里，代码如下：

         while(true)
         {
             Button_Scan(&button1);
             Button_Scan(&button2);
             Button_Scan(&button3);

             Delay(10);
         }

  ******************************************************************************
  */


/* 引用 -----------------------------------------------------------------------*/
#include "button.h"
#include <stddef.h>


/* 公开的函数 -------------------------------------------------------------------*/
/*
 * @简介：按钮初始化函数。在使用按钮的其它功能之前务必先调用此函数
 * @参数：Button 按钮结构体指针
 * @参数：Init   初始化参数，具体参考 @ref Button_InitTypeDef
 */
void Button_Init(Button_TypeDef *Button, Button_InitTypeDef *Init)
{
	/* 拷贝初始化参数 */
	Button->Init = *Init;

	/* 底层硬件初始化 */
	if(Button->Init.InitCallback != NULL)
	{
		Button->Init.InitCallback();
	}

	/* 设置参数初值 */
	Button->PreviousKeyState = 1;
	Button->DebounceTimeOut = 0;
	Button->LongPressRepeatCount = 0;
	Button->PreviousPressTime = 0;
}

/*
 * @简介：按钮扫描函数，执行按钮扫描动作。需要被等间隔重复调用，一般推荐以10ms~20ms为间隔调用该函数。
 * @参数：Button 按钮结构体指针
 */
void Button_Scan(Button_TypeDef *Key)
{
	/* 获取当前时间 */
	uint32_t now = Key->Init.GetTimeCallback();

	/* 检查消抖过程是否已经结束 */
	if(now > Key->DebounceTimeOut)
	{
		/* 读取按钮IO引脚的当前状态 */
		uint8_t currentKeyState = Key->Init.ReadPinStateCallback();

		/* 如果和之前的状态不相等则说明按钮发生了动作 */
		if(currentKeyState != Key->PreviousKeyState)
		{
			/* 下降沿，表示按钮被按下 */
			if(currentKeyState == 0)
			{
				Key->PreviousPressTime = now;
			}
			else /* 上升沿，表示按钮被松开 */
			{
				/* 按钮短按，触发PressCallback回调函数 */
				if(now - Key->PreviousPressTime < Key->Init.LongPressTime)
				{
					if(Key->Init.ClickedCallback != NULL)
					{
						Key->Init.ClickedCallback();
					}
				}

				/* 长按计数清零 */
				Key->LongPressRepeatCount = 0;
			}

			/* 设置消抖超时时间 */
			Key->DebounceTimeOut = now + 10;

			/* 更新按钮状态 */
			Key->PreviousKeyState = currentKeyState;
		}
		else
		{
			/* 处理按钮长按和长按重复触发 */
			/* 按钮是否处于按下状态 */
			if(currentKeyState == 0)
			{
				/* 长按首次触发 */
				if(Key->LongPressRepeatCount == 0)
				{
					/* 按下时间大于LongPressTime才能被视为长按 */
					if(now - Key->PreviousPressTime >= Key->Init.LongPressTime)
					{
						/* 设置长按重复触发计数 */
						Key->LongPressRepeatCount = 1;

						/* 触发长按回调函数 */
						if(Key->Init.LongPressCallback != NULL)
						{
							Key->Init.LongPressCallback(Key->LongPressRepeatCount); // 首次长按
						}

						/* 记录长按触发时间 */
						Key->PreviousRepeatTime = now;
					}
				}
				else /* 长按重复触发 */
				{
					/* 间隔大于LongPressRepeatInterval视为重复触发 */
					if(now - Key->PreviousRepeatTime >= Key->Init.LongPressRepeatInterval)
					{
						/* 递增长按触发计数 */
						Key->LongPressRepeatCount++;

						/* 触发长按回调函数 */
						if(Key->Init.LongPressCallback != NULL)
						{
							Key->Init.LongPressCallback(Key->LongPressRepeatCount); // 长按重复
						}

						/* 记录长按触发时间 */
						Key->PreviousRepeatTime = now;
					}
				} /* if(Key->LongPressRepeatCount == 0) */

			} /* if(currentKeyState == 0) */
		}
	}
}
