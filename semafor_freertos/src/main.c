#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void Sys_Config();
void GPIO_Config();
void USART_Config();


void Master_Task_Handler(void *params);
void Slave_Task_Handle(void *params);

xQueueHandle xQueue = NULL;
xSemaphoreHandle xSemphore = NULL;

char mymessage[100];



void printMessage(char *message){

	for(int i=0; i< strlen(message);i++){

		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) != SET);
		USART_SendData(USART2,message[i]);
	}
}
int main(void)
{

	RCC_DeInit();

	SystemCoreClockUpdate();

	Sys_Config();

	xQueue = xQueueCreate(1, sizeof(unsigned int));

	vSemaphoreCreateBinary(xSemphore);

	if( (xQueue != NULL ) && (xSemphore != NULL)){

		xTaskCreate(Master_Task_Handler , "Master Task" , 500 , NULL , 3 , NULL);
		xTaskCreate(Slave_Task_Handle , "Slave Task" , 500 , NULL , 1 , NULL);
		vTaskStartScheduler();

	}


  while (1)
  {

  }
}

void Master_Task_Handler(void *params){

	unsigned int xMasterId;
	portBASE_TYPE xStatus;

	xSemaphoreGive(xSemphore);

	while(1){

		xMasterId = (rand() & 0x1FF);

		xStatus = xQueueSend(xQueue , &xMasterId , portMAX_DELAY);

		if(xStatus != pdPASS){

			sprintf(mymessage , "Could not sent to the queue\r\n");
			printMessage(mymessage);
		}

		else{

			xSemaphoreGive(xSemphore);

			taskYIELD();
		}
	}
}

void SlaveDoWork(unsigned int passId){

	sprintf(mymessage , "Pass Id: %d\r\n" , passId);
	printMessage(mymessage);

	vTaskDelay(passId);

}


void Slave_Task_Handle(void *params){

	unsigned int xSlaveId;

	portBASE_TYPE xStatus;


	while(1){

		xSemaphoreTake(xSemphore , 0);

		xStatus = xQueueReceive(xQueue , &xSlaveId , 0);

		if(xStatus != pdPASS){

			sprintf(mymessage , "Queue is empty \r\n");
			printMessage(mymessage);

		}
		else{

			SlaveDoWork(xSlaveId);
		}

	}

}

void Sys_Config(){

	GPIO_Config();
	USART_Config();

}

void GPIO_Config(){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);

	GPIO_Init(GPIOA,&GPIO_InitStruct);


}

void USART_Config(){

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

	USART_InitTypeDef USART_InitStruct = {0};

	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;

	USART_Init(USART2,&USART_InitStruct);



	USART_Cmd(USART2,ENABLE);

}













void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
