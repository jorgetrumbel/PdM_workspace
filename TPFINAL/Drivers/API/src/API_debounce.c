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

/* Private define ------------------------------------------------------------*/

#define DEBOUNCE_DELAY 40


/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

// Variable de estado
static debounce_t estadoActual;

/*Declaracion de las estructuras de delays para leds*/
static delay_t delayDebounce;

static bool button_pressed_status;

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

	button_pressed_status = false;

	/* Initialize BSP PB for BUTTON_USER */
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	delayInit(&delayDebounce, DEBOUNCE_DELAY);

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
}

bool get_button_pressed_status(void){
	bool retVal = button_pressed_status;
	button_pressed_status = false;
	return retVal;
}
/* Private functions ---------------------------------------------------------*/

void buttonPressed(void){
	button_pressed_status = true;
}

void buttonReleased(void){

}
