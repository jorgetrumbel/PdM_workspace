/**
  ******************************************************************************
  * @file	API_led_handler.c
  * @author AV
  * @brief	Implementacion administrador de leds
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "API_led_handler.h"
#include "API_delay.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/*Declaracion de las estructuras de delays para leds*/
static delay_t delayLED1;
static delay_t delayLED2;
static delay_t delayLED3;

/*Arreglos con la info para cada LED*/
static Led_TypeDef boardLeds[LED_NUMBER] = {LED1,
											LED2,
											LED3};

static delay_t* delayLeds[LED_NUMBER] = {&delayLED1,
										 &delayLED2,
										 &delayLED3};

static ledMode_t ledOperationMode[LED_NUMBER] = {};
/* Private function prototypes -----------------------------------------------*/

/* Global functions *---------------------------------------------------------*/

void initLeds(void){
	/* Initialize BSP Leds and delays. Set leds operation mode to blink*/
	for(uint8_t currentLed = 0; currentLed < LED_NUMBER; currentLed++){
		BSP_LED_Init(boardLeds[currentLed]);
		ledOperationMode[currentLed] = MODE_LED_BLINK;
		delayInit(delayLeds[currentLed], 500);
	}
}

void ledUpdate(void){
	for(uint8_t currentLed = 0; currentLed < LED_NUMBER; currentLed++){
		if(delayRead(delayLeds[currentLed]) && ledOperationMode[currentLed] == MODE_LED_BLINK){
			BSP_LED_Toggle(boardLeds[currentLed]);
		}
	}
}

void ledModifyDuration(uint8_t ledNumber, uint32_t duration){
	delayWrite(delayLeds[ledNumber], duration);
}

void ledModifyOperationMode(uint8_t ledNumber, ledMode_t mode){
	ledOperationMode[ledNumber] = mode;
}

void ledModifyAllOperationMode(ledMode_t mode){
	for(uint8_t currentLed = 0; currentLed < LED_NUMBER; currentLed++){
		ledModifyOperationMode(currentLed, mode);
	}
}

void ledSetDiscrete(uint8_t ledNumber, ledState_t ledState){
	if(ledOperationMode[ledNumber] == MODE_LED_DISCRETE){
		if(ledState == LED_ON){
			BSP_LED_On(boardLeds[ledNumber]);
		}
		else if(ledState == LED_OFF){
			BSP_LED_Off(boardLeds[ledNumber]);
		}
	}
}

void ledSetAllDiscreteLeds(ledState_t ledState){
	for(uint8_t currentLed = 0; currentLed < LED_NUMBER; currentLed++){
		ledSetDiscrete(currentLed, ledState);
	}
}


/* Private functions ---------------------------------------------------------*/





/**
  * @brief
  * @param  None
  * @retval None
  */

