/******************************************************************//**
* @file   main.c
* @brief  Write a Program to use VCP.
* @version  v1.0
* @date   Apr 16, 2015
* @author Bhavin_Darji.Edutech Learning Solutions
**********************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "stm32f4_global.h"
#include "stm32f4_discovery_uart.h"
#include "stm32f4_discovery_vcp.h"
//#include "stm32f4_discovery.h"
//#include "stm32f4_ask25.h"
#include "stm32f4_gsm.h"



/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
  trace_printf("Hello\n");
  uint8_t i,gsmBuf[50] = {'\0'};
  uint8_t *location="2";
  uint8_t *number="198";
  uint8_t *name="RCare-TollFree";
  uint8_t *cmd0="AT+CPBW=?\r";
  uint8_t *cmd1 ="AT+CPBS=\"SM\"\r";
  uint8_t *get="ATE0\r";
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();

  /* USER CODE BEGIN 2 */
  BSP_UART_Init(9600);
  BSP_VCP_Init();

  vgetche(BLOCKING); // Dummy read to get the VCP Connected

  BSP_GSM_Cmd(get);
  vuprintf("Select the SIM Phonebook\n\r");
  BSP_GSM_Cmd(cmd1);
  BSP_GSM_ReadADV2(gsmBuf,45);
  for(i=0;i<=50;i++)
  {
    vuprintf("%c",gsmBuf[i]);
  }
  vuprintf("\n\r");
  vuprintf("Location range supported by the current Storage\n\r");
  BSP_GSM_Cmd(cmd0);
  BSP_GSM_ReadADV2(gsmBuf,45);
  for(i=0;i<=50;i++)
  {
    vuprintf("%c",gsmBuf[i]);
  }
  vuprintf("\n\r");
  vuprintf("Add new entry in phonebook\n\r");
  vuprintf("Location: %s , Number: %s , Name: %s\n\r",location,number,name);
  BSP_GSM_WritePB(location,number,name);
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

/** System Clock Configuration
*/
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
//  RCC_OscInitStruct.OscillatorType |= RCC_OSCILLATORTYPE_LSI;  // uncomment when LSI clock is used for RTC
//  RCC_OscInitStruct.LSIState = RCC_LSI_ON;        // uncomment when LSI Clock is used for RTC
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1
                              |RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

#ifdef USE_STM32F4_RTC
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_HSE_DIV8;  // Comment this line if you want to use LSI clock
//  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;     // Remove comment if you want to use LSI clock
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
#endif /* USE_STM32F4_RTC */

#ifdef USE_STM32F4_TSC
  /* Enable the CRC Module */
  __HAL_RCC_CRC_CLK_ENABLE();
#endif
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */

/**
  * @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
