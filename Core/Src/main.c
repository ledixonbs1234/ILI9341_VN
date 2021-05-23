/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ili9341.h"
#include "font_ubuntu_mono_24.h"
#include "controller.h"

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
TIM_HandleTypeDef htim4;

/* USER CODE BEGIN PV */
uint32_t number;
char buffer[2];
char bufferNumber[3];
// extern char tanSo[10];
char bufferPulse[2];
extern uint16_t setNumber;
uint16_t setNumberOLD = 0;
extern uint8_t setPulse;
uint8_t setPulseOLD;
extern uint16_t setTanSo;
uint16_t setTanSoOLD;
uint32_t count = 10;
extern int encoderVal;
char bufferTest[3];
char bufferTest1[10];
char bufferTest2[10];
char bufferCheDoNumber[10];
extern uint32_t test1;
extern uint32_t test2;
extern uint32_t countTest;
extern Tan_so tan_so;
extern uint8_t cheDoNumber;
uint8_t cheDoNumberOLD;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void createScreen()
{

  //kiem tra gia tri truoc do
  if (setTanSo == setTanSoOLD && setNumber == setNumberOLD && setPulse == setPulseOLD && cheDoNumber == cheDoNumberOLD)
  {
    return;
  }
  setTanSoOLD = setTanSo;
  setNumberOLD = setNumber;
  setPulseOLD = setPulse;
  cheDoNumberOLD = cheDoNumber;


  ili_fill_rect(40, 30, 200, 110, ILI_COLOR_DARKCYAN);



  
  //cap nhat mui ten
  switch (tan_so)
  {
  case PULSE_NUMBER:
    ili_draw_rectangle(80,60,5,50,ILI_COLOR_ORANGE);
    break;
  case PULSE_FRE:
  ili_draw_rectangle(120,60,5,50,ILI_COLOR_ORANGE);
    break;
  case PULSE_PULSE:
  ili_draw_rectangle(170,60,5,50,ILI_COLOR_ORANGE);
    break;

  default:
    break;
  }
  itoa(cheDoNumber, bufferCheDoNumber, 10);
  ili_draw_string_withbg(80, 40, bufferCheDoNumber, ILI_COLOR_WHITE, ILI_COLOR_BLUE, &font_ubuntu_mono_24);
  //thuc hien tao man hinh
  //hien so dau tien
  itoa(setNumber, bufferNumber, 10);
  ili_draw_string_withbg(70, 90, bufferNumber, ILI_COLOR_WHITE, ILI_COLOR_BLUE, &font_ubuntu_mono_24);
  // hien h khzfftoi
  ili_draw_string_withbg(110, 90, setTanSo == 0 ? "Hz" : "KHz", ILI_COLOR_WHITE, ILI_COLOR_BLUE, &font_ubuntu_mono_24);
  // hien % xung
  itoa(setPulse, bufferPulse, 10);
  ili_draw_string_withbg(160, 90, bufferPulse, ILI_COLOR_WHITE, ILI_COLOR_BLUE, &font_ubuntu_mono_24);
  ili_draw_string_withbg(200, 90, "%", ILI_COLOR_WHITE, ILI_COLOR_BLUE, &font_ubuntu_mono_24);

  itoa(countTest, bufferTest, 10);
  ili_draw_string_withbg(70, 110, bufferTest, ILI_COLOR_WHITE, ILI_COLOR_BLUE, &font_ubuntu_mono_24);

  itoa(test1, bufferTest1, 10);
  ili_draw_string_withbg(90, 110, bufferTest1, ILI_COLOR_WHITE, ILI_COLOR_BLUE, &font_ubuntu_mono_24);

  itoa(test2, bufferTest2, 10);
  ili_draw_string_withbg(140, 110, bufferTest2, ILI_COLOR_WHITE, ILI_COLOR_BLUE, &font_ubuntu_mono_24);

  HAL_Delay(50);
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
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  ili_init();
  ili_rotate_display(3);
  ili_fill_screen(ILI_COLOR_DARKGREY);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    createScreen();
    // count++;
    //  itoa(encoderVal, buffer, 10);
    //  ili_set_address_window(0,0,50,50);
    //  ili_fill_rect(0,0,100,100,ILI_COLOR_DARKCYAN);
    //  ili_draw_string_withbg(50, 40, buffer, ILI_COLOR_WHITE, ILI_COLOR_DARKGREEN, &font_ubuntu_mono_24);
    //ili_draw_pixel(20,20,ILI_COLOR_BLUE);
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
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
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
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 71;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 999;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 500;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
