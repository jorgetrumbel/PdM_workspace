/**
  ******************************************************************************
  * @file    API_debounce.h
  * @author  AV
  * @brief   Header de API de anti-rebote
  ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __API_DEBOUNCE_H
#define __API_DEBOUNCE_H

/* Includes ------------------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */



/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/**
  * @brief  Funcion para verificar si el pulsador fue presionado
  * @retval	Booleano indicando si el pulsador fue presionado
  */
bool get_button_pressed_status(void);

/**
  * @brief  Funcion para inicializar el control de anti rebote
  * @retval	Booleano indicando correcta inicializacion
  */
bool debounceInit(void);

/**
  * @brief  Funcion para actualizar la maquina de estados del control anti rebote
  */
void debounceUpdate(void);


#endif /* __API_DEBOUNCE_H */
