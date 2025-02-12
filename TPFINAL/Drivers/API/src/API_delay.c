/**
  ******************************************************************************
  * @file	API_delay.c
  * @author AV
  * @brief	Implementacion de delay no bloqueante
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "API_delay.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define NULL_POINTER	0

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Global functions *---------------------------------------------------------*/
void delayInit( delay_t * delay, tick_t duration ){
	if(delay != NULL_POINTER){
		delay->duration = duration;
		delay->running = false;
		delay->startTime = 0;
	}
}

bool_t delayRead( delay_t * delay ){
	bool_t delayReady = false;
	if(delay != NULL_POINTER){
		if(!delay->running){
			delay->running = true;
			delay->startTime = HAL_GetTick();
		}

		else{
			delayReady = ((HAL_GetTick() - delay->startTime) >= delay->duration);
			if (delayReady)
				delay->running = false;
		}

	}
	return delayReady;
}

void delayWrite( delay_t * delay, tick_t duration ){
	if(delay != NULL_POINTER)
		delay->duration = duration;
}

/* Private functions ---------------------------------------------------------*/





/**
  * @brief
  * @param  None
  * @retval None
  */

