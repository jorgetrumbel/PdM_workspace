/**
  ******************************************************************************
  * @file    API_delay.h
  * @author  AV
  * @brief   Header de delay no bloqueante
  ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __API_DELAY_H
#define __API_DELAY_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */



/* Exported types ------------------------------------------------------------*/

typedef uint32_t tick_t;

typedef bool bool_t;

typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/**
  * @brief  Funcion para inicializar un delay no bloqueante
  * @param  delay: puntero a la estructura delay_t
  * @param 	duration: duracion del delay
  */
void delayInit( delay_t * delay, tick_t duration );

/**
  * @brief  Funcion para leer el estado del delay e iniciarlo
  * @param  delay: puntero a la estructura delay_t
  * @retval bool_t estado del delay
  */
bool_t delayRead( delay_t * delay );

/**
  * @brief  Funcion para cambiar la duracion del delay
  * @param  delay: puntero a la estructura delay_t
  * @param 	duration: duracion del delay
  */
void delayWrite( delay_t * delay, tick_t duration );


#endif /* __API_DELAY_H */
