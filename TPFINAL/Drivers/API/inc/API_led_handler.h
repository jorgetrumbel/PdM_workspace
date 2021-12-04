/**
  ******************************************************************************
  * @file    API_led_handler.h
  * @author  AV
  * @brief   Header de API de leds
  ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __API_LED_HANDLER_H
#define __API_LED_HANDLER_H

/* Includes ------------------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h"


/* Exported types ------------------------------------------------------------*/

// enumerado con estados de aplicacion
typedef enum{
    MODE_LED_BLINK,
	MODE_LED_DISCRETE
} ledMode_t;

// enumerado con estados de aplicacion
typedef enum{
    LED_ON,
	LED_OFF,

} ledState_t;

/* Exported constants --------------------------------------------------------*/

#define LED_NUMBER 3

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */



/**
  * @brief  Funcion para inicializar los leds del board
  */
void initLeds(void);

/**
  * @brief  Funcion para actualizar el estado de blink de los leds.
  */
void ledUpdate(void);

/**
  * @brief  Funcion para modificar la duracion de blink de un led
  * @param  ledNumber: Numero de led
  * @param  duration: Nueva duracion de blink
  */
void ledModifyDuration(uint8_t ledNumber, uint32_t duration);

/**
  * @brief  Funcion para modificar la forma de operar un led, entre blink y discreto
  * @param  ledNumber: Numero de led
  * @param  mode: Nuevo modo de funcionamiento
  */
void ledModifyOperationMode(uint8_t ledNumber, ledMode_t mode);

/**
  * @brief  Funcion para modificar la forma de operar todos los leds, entre blink y discreto
  * @param  mode: Nuevo modo de funcionamiento
  */
void ledModifyAllOperationMode(ledMode_t mode);

/**
  * @brief  Funcion para setear el estado de un led
  * @param  ledNumber: Numero de led
  * @param  mode: Nuevo estado de led
  */
void ledSetDiscrete(uint8_t ledNumber, ledState_t ledState);

/**
  * @brief  Funcion para setear el estado de todos los leds
  * @param  mode: Nuevo estado de led
  */
void ledSetAllDiscreteLeds(ledState_t ledState);

#endif /* __API_LED_HANDLER_H */
