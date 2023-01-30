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
void Software_Interrupt_Config();

void Handler_Task(void *params);
void Periodic_Task_Handler(void *params);

xSemaphoreHandle xCountingSemphore = NULL;

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


	xSemaphoreCreateCounting(10 , 0);

		if( (xCountingSemphore != NULL)){

			void Software_Interrupt_Config();

			xTaskCreate(Handler_Task , "Master Task" , 500 , NULL , 1 , NULL);
			xTaskCreate(Periodic_Task_Handler , "Slave Task" , 500 , NULL , 3 , NULL);
			vTaskStartScheduler();

		}
  while (1)
  {

  }
}


void Software_Interrupt_Config(){

	NVIC_SetPriority(EXTI15_10_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);

	NVIC_EnableIRQ(EXTI15_10_IRQn);

}

void EXTI15_10_IRQnHandler(){

	portBASE_TYPE xHigherPriorityTaskwoken = pdFALSE;

	sprintf(mymessage , "Interrupt is Active \r\n");
	printMessage(mymessage);

	xSemaphoreGiveFromISR(xCountingSemphore, &xHigherPriorityTaskwoken);
	xSemaphoreGiveFromISR(xCountingSemphore, &xHigherPriorityTaskwoken);
	xSemaphoreGiveFromISR(xCountingSemphore, &xHigherPriorityTaskwoken);
	xSemaphoreGiveFromISR(xCountingSemphore, &xHigherPriorityTaskwoken);
	xSemaphoreGiveFromISR(xCountingSemphore, &xHigherPriorityTaskwoken);

	portEND_SWITCHING_ISR(xHigherPriorityTaskwoken);
}


void Handler_Task(void *params){

	while(1){

		xSemaphoreTake(xCountingSemphore, portMAX_DELAY);

		sprintf(mymessage , "Handler Task: Processing Event \r\n");
		printMessage(mymessage);
	}

}
void Periodic_Task_Handler(void *params){

	while(1){

		vTaskDelay(pdMS_TO_TICKS(500));

		sprintf(mymessage , "Periodic Task: Pending the Interrupt \r\n");
		printMessage(mymessage);

		NVIC_SetPendingIRQ(EXTI15_10_IRQn);

		sprintf(mymessage, "Periodic Task Resuming \r\n");
		printMessage(mymessage);

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


uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
