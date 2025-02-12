/**
  ******************************************************************************
  * @file	API_uart.c
  * @author AV
  * @brief	Implementacion de UART
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "API_uart.h"
#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* UART handler declaration */
UART_HandleTypeDef UartHandle;

uint8_t aRXBufferUser[RX_BUFFER_SIZE];
uint8_t aRXBufferA[RX_BUFFER_SIZE];
uint8_t aRXBufferB[RX_BUFFER_SIZE];

//static uint32_t registerReader;

static bool rxFlag;

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


	rxFlag = false;

	if (HAL_UART_Init(&UartHandle) != HAL_OK)
	  retVal = false;

	if( HAL_OK != HAL_UART_Receive_IT(&UartHandle, aRXBufferUser, RX_BUFFER_SIZE)){
		retVal = false;
	}

	if(retVal == true){
		char baudRateStr[] = "Baudrate: 9600\n\r";
		char wordLengthStr[] = "Word Legth: 8\n\r";
		char parityStr[] = "Parity: ODD\n\r";
		char stopBitsStr[] = "Stop Bits: 1\n\r";
		char buffer[256] = {};
		sprintf(buffer, "BaudRate con sprintf: %d \n\r", 9600);
		HAL_UART_Transmit(&UartHandle, (uint8_t*)baudRateStr, sizeof(baudRateStr)/sizeof(char), 10000);
		HAL_UART_Transmit(&UartHandle, (uint8_t*)wordLengthStr, sizeof(wordLengthStr)/sizeof(char), 10000);
		HAL_UART_Transmit(&UartHandle, (uint8_t*)stopBitsStr, sizeof(stopBitsStr)/sizeof(char), 10000);
		HAL_UART_Transmit(&UartHandle, (uint8_t*)parityStr, sizeof(parityStr)/sizeof(char), 10000);
		HAL_UART_Transmit(&UartHandle, (uint8_t*)buffer, sizeof(buffer)/sizeof(char), 10000);
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

bool getRxFlag(void){
	bool retVal = rxFlag;
	rxFlag = false;
	return retVal;
}

void getRxBuffer(uint8_t * pbuffer){
	for (uint8_t i = 0; i < RX_BUFFER_SIZE; i++){
		*(pbuffer + i) = aRXBufferA[i];
	}
}

void echoBuffer(void){
	HAL_UART_Transmit(&UartHandle, aRXBufferA, RX_BUFFER_SIZE, 10000);
}
/* Private functions ---------------------------------------------------------*/


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle){
	rxFlag = true;
	for (uint8_t i = 0; i < RX_BUFFER_SIZE; i++){
		aRXBufferA[i] = aRXBufferUser[i];
	}
	/*
	registerReader = UartHandle->Instance->DR;
	UartHandle->Instance->CR1 |= 0b100000;
	UartHandle->Instance->CR1 |= 0b1000000000;
	UartHandle->Instance->CR3 |= 0b1;
	UartHandle->RxState = HAL_UART_STATE_BUSY_RX;
	UartHandle->RxXferCount = RX_BUFFER_SIZE;
	UartHandle->pRxBuffPtr = aRXBufferUser;*/
	UART_Start_Receive_IT(UartHandle, aRXBufferUser, RX_BUFFER_SIZE);
}


void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart){
}

/**
  * @brief This function handles USART3 global interrupt.
  */
void USART3_IRQHandler(void)
{
  HAL_UART_IRQHandler(&UartHandle);
}

/**
  * @brief
  * @param  None
  * @retval None
  */

