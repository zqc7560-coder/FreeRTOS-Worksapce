/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
static QueueHandle_t xQueue1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
static int KeyScan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState *Previous);
static void vKeyTask(void *pvParameters);
static void vMonkeyTask(void *pvParameters);
static void PrintString(const char *Str);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

//
// @作用：扫描按钮以捕捉点击动作，有点击动作返回1，否则返回0
// @参数：Previous - 上次按钮的状态，从外部传入
//
static int KeyScan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState *Previous)
{
	int ret = 0;
	GPIO_PinState current = HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);

	if(current != *Previous && current == GPIO_PIN_SET)
	{
		ret = 1; // 检测到按钮点击动作，将返回值设置为1
	}

	*Previous = current;
	return ret;
}

// 按钮任务，KEY的处理方式
static void vKeyTask(void *pvParameters)
{
    GPIO_PinState key1Previous = GPIO_PIN_SET; // 上次按钮的值，作为参数传入
    GPIO_PinState key2Previous = GPIO_PIN_SET; // 上次按钮的值，作为参数传入
    GPIO_PinState key3Previous = GPIO_PIN_SET; // 上次按钮的值，作为参数传入
    GPIO_PinState key4Previous = GPIO_PIN_SET; // 上次按钮的值，作为参数传入

    for(;;)
    {
        // 如果检测到KEY1被按下
        if(KeyScan(KEY1_GPIO_Port, KEY1_Pin, &key1Previous))
        {
            // 那么就把数字1发送给队列xQueue1（排到队尾）
            int num = 1;
            xQueueSend(xQueue1, &num, portMAX_DELAY);
        }

        if(KeyScan(KEY2_GPIO_Port, KEY2_Pin, &key2Previous))
		   {
			   // 那么就把数字2发送给队列xQueue1（排到队尾）
			   int num = 2;
			   xQueueSend(xQueue1, &num, portMAX_DELAY);
		   }

        if(KeyScan(KEY3_GPIO_Port, KEY3_Pin, &key3Previous))
		   {
			   // 那么就把数字3发送给队列xQueue1（排到队尾）
			   int num = 3;
			   xQueueSend(xQueue1, &num, portMAX_DELAY);
		   }

        if(KeyScan(KEY4_GPIO_Port, KEY4_Pin, &key4Previous))
		   {
			   // 那么就把数字4发送给队列xQueue1（排到队尾）
			   int num = 4;
			   xQueueSend(xQueue1, &num, portMAX_DELAY);
		   }

        // 按钮扫描间隔是10毫秒
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

//猴子任务(接收队列消息)
static void vMonkeyTask(void *pvParameters)
{
    int num;
    for(;;)
    {
        xQueueReceive(xQueue1, &num, portMAX_DELAY); // 从队列当中接收一个项目
        // 根据接收到的数据表演不同的节目
        if(num == 1)        { PrintString("骑自行车"); }
        else if(num == 2)   { PrintString("翻跟斗"); }
        else if(num == 3)   { PrintString("滑滑板"); }
        else if(num == 4)   { PrintString("抛球"); }

        // 延迟20*50ms = 1秒，模拟动作表演的过程
        for(int i=0;i<20;i++)
        {
            PrintString("."); // 每次打一个点出来，方便观察
            vTaskDelay(pdMS_TO_TICKS(50));
        }
        PrintString("\n"); // 打印换行符
    }
}

static void PrintString(const char *Str)
{
	vTaskSuspendAll();

	HAL_UART_Transmit(&huart1, (const uint8_t *)Str, strlen(Str), HAL_MAX_DELAY);

	xTaskResumeAll();
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  xQueue1 = xQueueCreate(10, sizeof(int));		//创建队列

  xTaskCreate(vKeyTask, "key", 64, NULL, 2, NULL);
  xTaskCreate(vMonkeyTask, "monkey", 64, NULL, 1, NULL);

  vTaskStartScheduler();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LED3_Pin|LED1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : KEY3_Pin KEY4_Pin KEY1_Pin */
  GPIO_InitStruct.Pin = KEY3_Pin|KEY4_Pin|KEY1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LED3_Pin LED1_Pin */
  GPIO_InitStruct.Pin = LED3_Pin|LED1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : KEY2_Pin */
  GPIO_InitStruct.Pin = KEY2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(KEY2_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
