/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "AD9959.h"
#include "key.h"
// int fputc(int ch, FILE *f)
//{
//     uint8_t temp[1] = {ch};
//     HAL_UART_Transmit(&huart5, temp, 1, 2); //huart1 ???????????
//     return ch;
// }
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart5, (uint8_t *)&ch, 1, 0xFFFF);
  return ch;
}

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint32_t count1 = 0;
uint32_t DotFreChange;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void key_function(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t mode = 1; // mode = 1 ???? mode = ?????

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
  /* USER CODE BEGIN 1 */

  uint8_t CFR2_DATA[2] = {0x20, 0x00};
  uint32_t SinFre[5] = {1000, 1000, 1000, 1000};
  uint32_t SinPhr[5] = {0, 0, 0, 0};
  uint32_t SinAmp[5] = {1023 * 2, 1023, 1023, 1023};
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
  MX_UART5_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  Init_AD9959();
  WriteData_AD9959(FR2_ADD, 2, CFR2_DATA, 1);

  //§Õ????????
  Write_frequence(3, SinFre[3]);
  Write_frequence(0, SinFre[0]);
  Write_frequence(1, SinFre[1]);
  Write_frequence(2, SinFre[2]);

  /*---------------------------------------
  ???????????????????????
  Channel:  ???????
  Phase:    ???????,??¦¶??0~16383(???????0??~360??)
  ---------------------------------------*/
  Write_Phase(3, SinPhr[3]);
  Write_Phase(0, SinPhr[0]);
  Write_Phase(1, SinPhr[1]);
  Write_Phase(2, SinPhr[2]);

  /*
  ????????????????????????
Channel:  ???????
Ampli:    ????????,??¦¶0~1023???????0~1023???????????0~530mV????
*/
  Write_Amplitude(0, SinAmp[0]);
  Write_Amplitude(1, SinAmp[0]);

  Write_Amplitude(2, SinAmp[0]);
  Write_Amplitude(3, SinAmp[0]);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
printf("step_add");
    /* USER CODE BEGIN 3 */

    key_function();
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

  /** Configure the main internal regulator output voltage
   */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 144;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
  extern uint32_t count1;
  extern uint16_t stepFreChange;
  HAL_Delay(100);
  printf("step_add");
  if (GPIO_Pin == KEY0_Pin)
  {
    printf("step_add");
    stepFreChange = stepFreChange + 100;
  }
  if (GPIO_Pin == KEY1_Pin)
  {
    printf("step_reduce");
    if (stepFreChange > 0)
      stepFreChange = stepFreChange - 100;
    if (GPIO_Pin == KEY1_Pin)
    {
      mode++;
      mode = mode % 2;
    }
  }
}
void key_function(void)
{
  extern uint32_t NowFre;
  extern uint32_t count1;
  extern uint16_t stepFreChange;

  char key_confirm;
  key_confirm = KEY_SCAN();
  if (0 < key_confirm && key_confirm < 17)
  {   //????
    if (key_confirm == 2)
    {
      printf("Sweepstep_++\r\n");
      stepFreChange = stepFreChange + 100;
    }
    if (key_confirm == 3)
    {
      printf("Sweepstep_--\r\n");
      stepFreChange = stepFreChange - 100;
    }
    if (key_confirm == 1)    // ???§Ý?
    {
      NowFre = 1000;
      mode++;
      mode = mode % 2;
      if (mode % 2 == 0)
      {
        HAL_TIM_Base_Stop_IT(&htim2);
        HAL_TIM_Base_Start_IT(&htim2);
        stepFreChange = 1000;
        printf("mode = DotFre\r\n");
        Write_frequence(0, NowFre);
      }
      if (mode % 2 == 1)
      {
        HAL_TIM_Base_Stop_IT(&htim2);
        printf("mode = SweepFre\r\n");
        Write_frequence(0, NowFre);
      }
    }
    if (key_confirm == 6)
    {
      if (mode % 2 == 0)
      {
        DotFreChange = 1;
        printf("Dotstep_++\r\n");
      }
    }
    if (key_confirm == 7)
    {
      if (mode % 2 == 0)
      {

        DotFreChange = 2;
        printf("Dotstep_--\r\n");
      }
    }
  }
  /*?????*/
  if (mode % 2 == 0)
  {
    if (DotFreChange == 1)
    {
      DotFreChange = 0;
      NowFre = NowFre + 100000;
      Write_frequence(0, NowFre);
      // printf("NowFre=%d\r\n",NowFre);
    }
    if (DotFreChange == 2)
    {
      DotFreChange = 0;
      NowFre = NowFre - 1000;
      printf("NowFre=%d\r\n", NowFre);
      Write_frequence(0, NowFre);
    }
    printf("NowFre=%d\r\n", NowFre);
  }
}

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
