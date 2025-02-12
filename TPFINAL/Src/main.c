/**
  ******************************************************************************
  * @file    UART/UART_Printf/Src/main.c
  * @author  MCD Application Team
  * @brief   This example shows how to retarget the C library printf function
  *          to the UART.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "API_uart.h"
#include "API_debounce.h"
#include "API_led_handler.h"

/* Private typedef -----------------------------------------------------------*/

// enumerado con estados de aplicacion
typedef enum{
    STATE_LED_BLINK,
	STATE_LED_MANUAL,
	STATE_ERROR
} state_t;

/* Private define ------------------------------------------------------------*/

#define MANUAL_MODE_ACTIVATION_MESSAGE 1234
#define BLINK_MODE_ACTIVATION_MESSAGE 1234

#define MANUAL_MODE_LED_ON_MESSAGE 1000
#define MANUAL_MODE_LED_OFF_MESSAGE 0

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

static uint8_t messageReceivedString[] =  "\n\rMESSAGE RECEIVED \n\r";
static uint8_t nextLineString[] =  "\n\r";

static uint32_t ledDuration;

static uint8_t buffer[RX_BUFFER_SIZE] = {};
static char msgbuffer[100] = {};

static state_t app_state;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);

/**
  * @brief Realiza las funciones del estado Blink.
  * @param  None
  * @retval None
  */
static void ledBlinkStateUpdate(void);

/**
  * @brief Realiza las funciones del estado Manual.
  * @param  None
  * @retval None
  */
static void ledManualStateUpdate(void);

/**
  * @brief Realiza las funciones del estado Error.
  * @param  None
  * @retval None
  */
static void errorStateUpdate(void);

/**
  * @brief Realiza las acciones para cambiar al estado Error.
  * @param  None
  * @retval None
  */
static void switchToErrorState(void);

/**
  * @brief Realiza las acciones para cambiar al estado Manual.
  * @param  None
  * @retval None
  */
static void switchToLedManualState(void);

/**
  * @brief Realiza las acciones para cambiar al estado Blink.
  * @param  None
  * @retval None
  */
static void switchToLedBlinkState(void);

/**
  * @brief Verifica si el mensaje recibido es valido.
  * @param  pbuffer: puntero al arreglo de caracteres a verificar
  * @param  size: Cantidad de caracteres
  * @retval bool: Indica si el mensaje es valido
  */
static bool bufferChecker(uint8_t* pbuffer, uint16_t size);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	/* STM32F4xx HAL library initialization:
	   - Configure the Flash prefetch
	   - Systick timer is configured by default as source of time base, but user
		 can eventually implement his proper time base source (a general purpose
		 timer for example or other time source), keeping in mind that Time base
		 duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
		 handled in milliseconds basis.
	   - Set NVIC Group Priority to 4
	   - Low Level Initialization
	 */
	HAL_Init();

	/* Configure the system clock to 180 MHz */
	SystemClock_Config();

	initLeds();

	debounceInit();

	uartInit();

	app_state = STATE_LED_BLINK;

	/* Infinite loop */
	while (1)
	{
	  debounceUpdate();

	  ledUpdate();

	  switch(app_state){
		  case STATE_LED_BLINK:
		  {
			  ledBlinkStateUpdate();
			  break;
		  }
		  case STATE_LED_MANUAL:
		  {
			  ledManualStateUpdate();
			  break;
		  }
		  case STATE_ERROR:
		  {
			  errorStateUpdate();
			  break;
		  }
		  default:
		  {
			  switchToErrorState();
			  break;
		  }
	  }


	}
}


static bool bufferChecker(uint8_t* pbuffer, uint16_t size){
	bool retVal = true;
	for(uint8_t i = 0; i < size; i++){
		if(*(pbuffer + i) > '9' || *(pbuffer + i) < '0'){
			retVal = false;
		}
	}
	return retVal;
}

static void ledBlinkStateUpdate(void){
	if(getRxFlag()){
		uartSendString(messageReceivedString);
		echoBuffer();
		uartSendString(nextLineString);
		getRxBuffer(buffer);
		if(bufferChecker(buffer, RX_BUFFER_SIZE)){
			ledDuration = (buffer[1] - '0') * 1000 + (buffer[2] - '0') * 100 + (buffer[3] - '0') * 10 + buffer[4] - '0';
			if((buffer[0] - '1') < 3 && buffer[0] > '0'){
				ledModifyDuration(buffer[0] - '1', ledDuration);
				sprintf(msgbuffer, "LED %d duration: %d \n\r", buffer[0] - '0',(int)ledDuration);
				uartSendString((uint8_t*)msgbuffer);
			}
			else if((buffer[0] - '0') == 0){
				if(ledDuration == MANUAL_MODE_ACTIVATION_MESSAGE){
					switchToLedManualState();

				}
			}
		}
	}
	if(get_button_pressed_status()){
		switchToErrorState();
	}
}

static void ledManualStateUpdate(void){
	if(getRxFlag()){
		uartSendString(messageReceivedString);
		echoBuffer();
		uartSendString(nextLineString);
		getRxBuffer(buffer);
		if(bufferChecker(buffer, RX_BUFFER_SIZE)){
			ledDuration = (buffer[1] - '0') * 1000 + (buffer[2] - '0') * 100 + (buffer[3] - '0') * 10 + buffer[4] - '0';
			if((buffer[0] - '0') < 4 && buffer[0] > '0'){
				if(MANUAL_MODE_LED_OFF_MESSAGE == ledDuration){
					ledSetDiscrete(buffer[0] - '1', LED_OFF);
					sprintf(msgbuffer, "LED %d OFF \n\r", buffer[0] - '0');
					uartSendString((uint8_t*)msgbuffer);
				}
				else if(MANUAL_MODE_LED_ON_MESSAGE == ledDuration){
					ledSetDiscrete(buffer[0] - '1', LED_ON);
					sprintf(msgbuffer, "LED %d ON \n\r", buffer[0] - '0');
					uartSendString((uint8_t*)msgbuffer);
				}
			}
			else if((buffer[0] - '0') == 0){
				if(ledDuration == BLINK_MODE_ACTIVATION_MESSAGE){
					switchToLedBlinkState();
				}
			}
		}
	}
}

static void errorStateUpdate(void){
	if(getRxFlag()){
		uartSendString(messageReceivedString);
		echoBuffer();
		uartSendString(nextLineString);
		getRxBuffer(buffer);
		if(bufferChecker(buffer, RX_BUFFER_SIZE)){
			ledDuration = (buffer[1] - '0') * 1000 + (buffer[2] - '0') * 100 + (buffer[3] - '0') * 10 + buffer[4] - '0';
			if((buffer[0] - '0') == 0){
				if(ledDuration == BLINK_MODE_ACTIVATION_MESSAGE){
					switchToLedBlinkState();
				}
			}
		}
	}
}

static void switchToErrorState(void){
	ledModifyAllOperationMode(MODE_LED_DISCRETE);
	ledSetAllDiscreteLeds(LED_OFF);
	sprintf(msgbuffer, "Switching to error mode \n\r");
	uartSendString((uint8_t*)msgbuffer);
	app_state = STATE_ERROR;
}

static void switchToLedManualState(void){
	ledModifyAllOperationMode(MODE_LED_DISCRETE);
	ledSetAllDiscreteLeds(LED_OFF);
	sprintf(msgbuffer, "Switching to manual mode \n\r");
	uartSendString((uint8_t*)msgbuffer);
	app_state = STATE_LED_MANUAL;
}

static void switchToLedBlinkState(void){
	ledModifyAllOperationMode(MODE_LED_BLINK);
	sprintf(msgbuffer, "Switching to Blink mode \n\r");
	uartSendString((uint8_t*)msgbuffer);
	app_state = STATE_LED_BLINK;
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            PLL_R                          = 2
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
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
/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  while (1)
  {
  }
}
