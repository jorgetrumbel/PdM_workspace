/**
  ******************************************************************************
  * @file    API_delay.h
  * @author  AV
  * @brief   Header de UART
  ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __API_UART_H
#define __API_UART_H

/* Includes ------------------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h"



/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

#define RX_BUFFER_SIZE 5

/* User can use this section to tailor USARTx/UARTx instance used and associated
   resources */
/* Definition for USARTx clock resources */
#define USARTx                           USART3
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART3_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART3_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART3_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_8
#define USARTx_TX_GPIO_PORT              GPIOD
#define USARTx_TX_AF                     GPIO_AF7_USART3
#define USARTx_RX_PIN                    GPIO_PIN_9
#define USARTx_RX_GPIO_PORT              GPIOD
#define USARTx_RX_AF                     GPIO_AF7_USART3


#define USARTx_IRQn						 USART3_IRQn
/* Exported functions ------------------------------------------------------- */

void USART3_IRQHandler(void);

/**
  * @brief Inicializa la uart
  * @param  None
  * @retval bool: Devuelve si la inicializacion de la uart fue realizada correctamente
  */
bool uartInit(void);


/**
  * @brief Envia un string por uart
  * @param  pstring: String a ser enviado por uart
  * @retval None
  */
void uartSendString(uint8_t *pstring);

/**
  * @brief Verifica si se recibio un nuevo mensaje por uart.
  * @param  None
  * @retval bool: Indica si se recibio un mensaje nuevo
  */
bool getRxFlag(void);

/**
  * @brief Copia el mensaje almacenado en el buffer de la uart.
  * @param  pbuffer: String donde se desea guardar el mensaje recibido
  * @retval None
  */
void getRxBuffer(uint8_t * pbuffer);

/**
  * @brief Transmite por la uart el mensaje en el buffer de recepcion
  * @param  None
  * @retval None
  */
void echoBuffer(void);

#endif /* __API_UART_H */
