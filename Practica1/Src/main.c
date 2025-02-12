/**
  ******************************************************************************
  * @file    main.c
  * @author  AV
  * @brief   archivo source main del practico 1, implementacion de delays no bloqueantes
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include "main.h"

#include <stdio.h>

#include "API_delay.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

#define LED_NUMBER 3

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/*Declaracion de las estructuras de delays para leds*/
static delay_t delayLED1;
static delay_t delayLED2;
static delay_t delayLED3;


/*Se podria agrupar todo esto en una estructura, quedaria mas comodo el codigo*/

/*Arreglos con la info para cada LED*/
static Led_TypeDef boardLeds[LED_NUMBER] = {LED1,
											LED2,
											LED3};

static delay_t* delayLeds[LED_NUMBER] = {&delayLED1,
										 &delayLED2,
										 &delayLED3};

static tick_t delayLedsDuration[LED_NUMBER] =  {100,
												500,
												1000};

/* Private function prototypes -----------------------------------------------*/

static void SystemClock_Config(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

int main(void)
{
	/* STM32F4xx HAL library initialization*/
	HAL_Init();

	/* Configure the system clock to 180 MHz */
	SystemClock_Config();

	/* Initialize BSP Leds*/
	BSP_LED_Init(LED1);
	BSP_LED_Init(LED2);
	BSP_LED_Init(LED3);

	/*Inicializacion de delays no bloqueantes para leds*/
	for(uint8_t currentLed = 0; currentLed < LED_NUMBER; currentLed++){
	  delayInit(delayLeds[currentLed], delayLedsDuration[currentLed]);
	}

	/* Infinite loop */
	while (1)
	{
		for(uint8_t currentLed = 0; currentLed < LED_NUMBER; currentLed++){
			if(delayRead(delayLeds[currentLed])){
				BSP_LED_Toggle(boardLeds[currentLed]);
			}
		}
	}
}




static void SystemClock_Config(void)
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable Power Control clock */
	__HAL_RCC_PWR_CLK_ENABLE();

	/* The voltage scaling allows optimizing the power consumption when the device is
	   clocked below the maximum system frequency, to update the voltage scaling value
	   regarding system frequency refer to product datasheet.  */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 360;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}

	if(HAL_PWREx_EnableOverDrive() != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	   clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}
}


static void Error_Handler(void)
{
	/* Turn LED2 on */
	BSP_LED_On(LED2);
	while (1)
	{
	}
}

