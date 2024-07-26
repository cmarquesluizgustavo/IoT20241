/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include <stdio.h>
#include <string.h>
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
TIM_HandleTypeDef htim1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_tx;

/* USER CODE BEGIN PV */

void delay (uint16_t time)
{
	__HAL_TIM_SET_COUNTER(&htim1, 0);
	while (__HAL_TIM_GET_COUNTER (&htim1) < time);
}

int HCSR04_Read1(void)
{
	HAL_GPIO_WritePin(TRIGGER_PIN_GPIO_Port, TRIGGER_PIN_Pin, GPIO_PIN_SET);  // pull the TRIG pin HIGH
	delay(10);  // wait for 10 us
	HAL_GPIO_WritePin(TRIGGER_PIN_GPIO_Port, TRIGGER_PIN_Pin, GPIO_PIN_RESET);  // pull the TRIG pin low
	delay(100); // wait for 100 us

    // Leitura do tempo de resposta
	__HAL_TIM_SET_COUNTER(&htim1, 0);
    uint32_t startTick = __HAL_TIM_GET_COUNTER (&htim1);
    int state = (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET);
    while (state) {
    	state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET;

        if ((__HAL_TIM_GET_COUNTER (&htim1) - startTick) > 50000) {
            return -1;  // Timeout
        }
    }
    uint32_t startTime = __HAL_TIM_GET_COUNTER (&htim1);
    while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_SET) {
        if ((__HAL_TIM_GET_COUNTER (&htim1) - startTime) > 50000) {
            return -1;  // Timeout
        }
    }
    uint32_t endTime = __HAL_TIM_GET_COUNTER (&htim1);
    uint32_t duration = endTime - startTime;
    // Calcula a distância
    int distance = (duration * 0.0343) / 2; // Velocidade do som = 34300 cm/s
    return distance;
}


#define TRIG_PORT_MEIO 	GPIOB
#define TRIG_PIN_MEIO	GPIO_PIN_15
#define ECHO_PORT_MEIO 	GPIOB
#define ECHO_PIN_MEIO	GPIO_PIN_1

int HCSR04_Read2(void)
{
	HAL_GPIO_WritePin(TRIG_PORT_MEIO, TRIG_PIN_MEIO, GPIO_PIN_SET);  // pull the TRIG pin HIGH
	delay(10);  // wait for 10 us
	HAL_GPIO_WritePin(TRIG_PORT_MEIO, TRIG_PIN_MEIO, GPIO_PIN_RESET);  // pull the TRIG pin low
	delay(100); // wait for 100 us

    // Leitura do tempo de resposta
	__HAL_TIM_SET_COUNTER(&htim1, 0);
    uint32_t startTick = __HAL_TIM_GET_COUNTER (&htim1);
    int state = (HAL_GPIO_ReadPin(ECHO_PORT_MEIO, ECHO_PIN_MEIO) == GPIO_PIN_RESET);
    while (state) {
    	state = HAL_GPIO_ReadPin(ECHO_PORT_MEIO, ECHO_PIN_MEIO) == GPIO_PIN_RESET;

        if ((__HAL_TIM_GET_COUNTER (&htim1) - startTick) > 50000) {
            return -1;  // Timeout
        }
    }
    uint32_t startTime = __HAL_TIM_GET_COUNTER (&htim1);
    while (HAL_GPIO_ReadPin(ECHO_PORT_MEIO, ECHO_PIN_MEIO) == GPIO_PIN_SET) {
        if ((__HAL_TIM_GET_COUNTER (&htim1) - startTime) > 50000) {
            return -1;  // Timeout
        }
    }
    uint32_t endTime = __HAL_TIM_GET_COUNTER(&htim1);
    uint32_t duration = endTime - startTime;
    // Calcula a distância
    int distance = (duration * 0.0343) / 2; // Velocidade do som = 34300 cm/s
    return distance;
}

#define TRIG_PORT_DIREITA 	GPIOB
#define TRIG_PIN_DIREITA	GPIO_PIN_13
#define ECHO_PORT_DIREITA 	GPIOB
#define ECHO_PIN_DIREITA	GPIO_PIN_2

int HCSR04_Read3(void)
{
	HAL_GPIO_WritePin(TRIG_PORT_DIREITA, TRIG_PIN_DIREITA, GPIO_PIN_SET);  // pull the TRIG pin HIGH
	delay(10);  // wait for 10 us
	HAL_GPIO_WritePin(TRIG_PORT_DIREITA, TRIG_PIN_DIREITA, GPIO_PIN_RESET);  // pull the TRIG pin low
	delay(100); // wait for 100 us

    // Leitura do tempo de resposta
	__HAL_TIM_SET_COUNTER(&htim1, 0);
    uint32_t startTick = __HAL_TIM_GET_COUNTER (&htim1);
    int state = (HAL_GPIO_ReadPin(ECHO_PORT_DIREITA, ECHO_PIN_DIREITA) == GPIO_PIN_RESET);
    while (state) {
    	state = HAL_GPIO_ReadPin(ECHO_PORT_DIREITA, ECHO_PIN_DIREITA) == GPIO_PIN_RESET;

        if ((__HAL_TIM_GET_COUNTER (&htim1) - startTick) > 50000) {
            return -1;  // Timeout
        }
    }
    uint32_t startTime = __HAL_TIM_GET_COUNTER (&htim1);
    while (HAL_GPIO_ReadPin(ECHO_PORT_DIREITA, ECHO_PIN_DIREITA) == GPIO_PIN_SET) {
        if ((__HAL_TIM_GET_COUNTER (&htim1) - startTime) > 50000) {
            return -1;  // Timeout
        }
    }
    uint32_t endTime = __HAL_TIM_GET_COUNTER(&htim1);
    uint32_t duration = endTime - startTime;
    // Calcula a distância
    int distance = (duration * 0.0343) / 2; // Velocidade do som = 34300 cm/s
    return distance;
}

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	char MSG[40];
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
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  int esquerda, meio, direita;

  HAL_TIM_Base_Start(&htim1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  esquerda = HCSR04_Read1();
	  meio = HCSR04_Read2();
	  direita = HCSR04_Read3();
	  //sprintf(MSG, "Distance1 : %d cm \r\n", Distance1);
	  //HAL_UART_Transmit(&huart1, (uint8_t*)MSG, sizeof(MSG), 100);
	  //HAL_Delay(500);
	  //sprintf(MSG, "Distance2 : %d cm \r\n", Distance2);
	  //HAL_UART_Transmit(&huart1, (uint8_t*)MSG, sizeof(MSG), 100);
	  //HAL_Delay(500);
	  //sprintf(MSG, "Distance3 : %d cm \r\n", Distance3);
	  //HAL_UART_Transmit(&huart1, (uint8_t*)MSG, sizeof(MSG), 100);
	  //HAL_Delay(500);

	  //sprintf(MSG, "%d,  %d,  %d  \r\n", esquerda, meio, direita);
	  //HAL_UART_Transmit(&huart1, (uint8_t*)MSG, strlen(MSG), 100);


	  if(esquerda - direita > 5){
		  sprintf(MSG, "Va para a esquerda \r\n");
		  HAL_UART_Transmit(&huart1, (uint8_t*)MSG, strlen(MSG), 100);
	  }
	  else if(direita - esquerda > 5){
		  sprintf(MSG, "Va para a direita \r\n");
		  HAL_UART_Transmit(&huart1, (uint8_t*)MSG, strlen(MSG), 100);
	  }

	  if(meio < 40){
		  sprintf(MSG, "Fim da rua \r\n");
		  HAL_UART_Transmit(&huart1, (uint8_t*)MSG, strlen(MSG), 100);
	  }
	  HAL_Delay(500);

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 16-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_IC_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

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
  huart1.Init.BaudRate = 9600;
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
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);

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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13|TRIGGER_PIN_Pin|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB0 PB1 PB2 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB13 TRIGGER_PIN_Pin PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|TRIGGER_PIN_Pin|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

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

#ifdef  USE_FULL_ASSERT
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
