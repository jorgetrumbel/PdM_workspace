/**
  ******************************************************************************
  * @file	API_delay.c
  * @author AV
  * @brief	Implementacion de funcionces de anti rebote
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>

#include "API_debounce.h"
#include "API_delay.h"
#include "API_uart.h"

#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

/* Private typedef -----------------------------------------------------------*/

// enumerado con estados de pulsador
typedef enum{
    BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RISING
} debounce_t;

// enumerado con estados de LEDS
typedef enum{
    TOGGLE_TIME_DIFFERENT,
	TOGGLE_TIME_SAME
} ledToggleTime_t;

/* Private define ------------------------------------------------------------*/

#define DEBOUNCE_DELAY 40

#define LED_NUMBER 3

#define PUNTO3 //PUNTO2

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

// Variable de estado
static debounce_t estadoActual;

// Variable con estado de leds
static ledToggleTime_t estadoLeds;

/*Declaracion de las estructuras de delays para leds*/
static delay_t delayDebounce;


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

static tick_t delayLedsDuration[LED_NUMBER] =  {100,
												500,
												1000};

static char buffer[200] = {};
/* Private function prototypes -----------------------------------------------*/

/**
  * @brief  Funcion que se realiza cuando se presiona el boton
  */
void buttonPressed(void);

/**
  * @brief  Funcion que se realiza cuando se libera el boton
  */
void buttonReleased(void);

/* Global functions *---------------------------------------------------------*/

bool debounceInit(void){
	estadoActual = BUTTON_UP;

	/* Initialize BSP Leds*/
	BSP_LED_Init(LED1);
	BSP_LED_Init(LED2);
	BSP_LED_Init(LED3);

	/* Initialize BSP PB for BUTTON_USER */
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	delayInit(&delayDebounce, DEBOUNCE_DELAY);

	uartInit();

#ifdef PUNTO3
	estadoLeds = TOGGLE_TIME_DIFFERENT;
	/*Inicializacion de delays no bloqueantes para leds*/
	for(uint8_t currentLed = 0; currentLed < LED_NUMBER; currentLed++){
		delayInit(delayLeds[currentLed], delayLedsDuration[currentLed]);
	}
#endif

	return true;
}


void debounceUpdate(void){
	switch(estadoActual){
		case BUTTON_UP:{
			if(BSP_PB_GetState(BUTTON_USER)){
				delayRead(&delayDebounce);
				estadoActual = BUTTON_RISING;
			}
			break;
		}
		case BUTTON_RISING:{
			if(delayRead(&delayDebounce)){
				if(!BSP_PB_GetState(BUTTON_USER)){
					estadoActual = BUTTON_UP;
				}
				else{
					estadoActual = BUTTON_DOWN;
					buttonPressed();
				}
			}
			break;
		}
		case BUTTON_FALLING:{
			if(delayRead(&delayDebounce)){
				if(BSP_PB_GetState(BUTTON_USER)){
					estadoActual = BUTTON_DOWN;
				}
				else{
					estadoActual = BUTTON_UP;
					buttonReleased();
				}
			}
			break;
		}
		case BUTTON_DOWN:{
			if(!BSP_PB_GetState(BUTTON_USER)){
				delayRead(&delayDebounce);
				estadoActual = BUTTON_FALLING;
			}
			break;
		}
		default:{
			debounceInit();
			break;
		}
	}
#ifdef PUNTO3
	for(uint8_t currentLed = 0; currentLed < LED_NUMBER; currentLed++){
		if(delayRead(delayLeds[currentLed])){
			BSP_LED_Toggle(boardLeds[currentLed]);
		}
	}
#endif
}
/* Private functions ---------------------------------------------------------*/

#ifdef PUNTO2
void buttonPressed(void){
	BSP_LED_Toggle(LED1);
}

void buttonReleased(void){
	BSP_LED_Toggle(LED2);
}
#endif

#ifdef PUNTO3
void buttonPressed(void){
	if(estadoLeds == TOGGLE_TIME_DIFFERENT){
		for(uint8_t currentLed = 0; currentLed < LED_NUMBER; currentLed++){
			delayWrite(delayLeds[currentLed], 500);
			sprintf(buffer, "LED %d tiempo: %d\n\r",currentLed + 1, 500);
			uartSendString((uint8_t*)buffer);
		}
		estadoLeds = TOGGLE_TIME_SAME;
	}
	else if(estadoLeds == TOGGLE_TIME_SAME){
		for(uint8_t currentLed = 0; currentLed < LED_NUMBER; currentLed++){
			delayWrite(delayLeds[currentLed], delayLedsDuration[currentLed]);
			sprintf(buffer, "LED %d tiempo: %d\n\r", currentLed + 1, (int)delayLedsDuration[currentLed]);
			uartSendString((uint8_t*)buffer);
		}
		estadoLeds = TOGGLE_TIME_DIFFERENT;
	}
}

void buttonReleased(void){

}
#endif

/**
  * @brief
  * @param  None
  * @retval None
  */

