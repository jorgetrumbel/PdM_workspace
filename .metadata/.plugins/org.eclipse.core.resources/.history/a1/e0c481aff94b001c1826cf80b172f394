/**
  ******************************************************************************
  * @file	API_uart.c
  * @author AV
  * @brief	Implementacion de UART
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "API_uart.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* UART handler declaration */
UART_HandleTypeDef UartHandle;

/* Private function prototypes -----------------------------------------------*/

/* Global functions *---------------------------------------------------------*/

bool uartInit(void){

	bool retVal = true;
	/*##-1- Configure the UART peripheral ######################################*/
	/* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	/* UART configured as follows:
	  - Word Length = 8 Bits (7 data bit + 1 parity bit) :
					  BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
	  - Stop Bit    = One Stop bit
	  - Parity      = ODD parity
	  - BaudRate    = 9600 baud
	  - Hardware flow control disabled (RTS and CTS signals) */
	UartHandle.Instance        = USARTx;
	UartHandle.Init.BaudRate   = 9600;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits   = UART_STOPBITS_1;
	UartHandle.Init.Parity     = UART_PARITY_ODD;
	UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode       = UART_MODE_TX_RX;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(&UartHandle) != HAL_OK)
	  retVal = false;

	if(retVal == true){
		char baudRateStr[] = "Baudrate: 9600\n\r";
		char wordLengthStr[] = "Word Legth: 8\n\r";
		char parityStr[] = "Parity: ODD\n\r";
		char stopBitsStr[] = "Stop Bits: 1\n\r";
		HAL_UART_Transmit(&UartHandle, (uint8_t*)baudRateStr, sizeof(baudRateStr)/sizeof(char), 10000);
		HAL_UART_Transmit(&UartHandle, (uint8_t*)wordLengthStr, sizeof(wordLengthStr)/sizeof(char), 10000);
		HAL_UART_Transmit(&UartHandle, (uint8_t*)stopBitsStr, sizeof(stopBitsStr)/sizeof(char), 10000);
		HAL_UART_Transmit(&UartHandle, (uint8_t*)parityStr, sizeof(parityStr)/sizeof(char), 10000);
	}
	return retVal;
}

void uartSendString(uint8_t *pstring){
	uint8_t size = 0, currentChar = 10;
	while(size < 250 && currentChar != '\0'){
		currentChar = *(pstring + size);
		size++;
	}
	HAL_UART_Transmit(&UartHandle, pstring, (uint16_t)size, 10000);
}
/* Private functions ---------------------------------------------------------*/





/**
  * @brief
  * @param  None
  * @retval None
  */

