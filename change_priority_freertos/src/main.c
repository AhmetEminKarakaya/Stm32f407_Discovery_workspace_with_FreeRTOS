#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "FreeRTOS.h"
#include "task.h"

#include <string.h>
#include <stdio.h>

TaskHandle_t TaskHandle1 = NULL;
TaskHandle_t TaskHandle2 = NULL;

char mymessage[100];
uint8_t buton_state = 0;

void Sys_Config();
void GPIO_Config();
void USART_Config();
void EXTI_Config();

void Task1Handler(void *params);
void Task2Handler(void *params);

void EXTI0_IRQHandler(void){

	EXTI_ClearITPendingBit(EXTI_Line0);

	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_0) == Bit_SET){

		buton_state = 1;
	}

}

void print_message(char *message){


	for(int i=0; i<strlen(message); i++){

		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) != SET);
		USART_SendData(USART2,message[i]);

	}

}


int main(void)
{
	RCC_DeInit();

	SystemCoreClockUpdate();

	Sys_Config();

	xTaskCreate(Task1Handler,"Task1",configMINIMAL_STACK_SIZE,NULL,4,&TaskHandle1);
	xTaskCreate(Task2Handler,"Task2",configMINIMAL_STACK_SIZE,NULL,2,&TaskHandle2);

	vTaskStartScheduler();

  while (1)
  {

  }
}

void Task1Handler(void *params){

	UBaseType_t p1,p2;

	sprintf(mymessage,"Task1 calisiyor\r\n");
	print_message(mymessage);

	sprintf(mymessage,"Task1 onceligi: %d\r\n", uxTaskPriorityGet(TaskHandle1));
	print_message(mymessage);

	sprintf(mymessage,"Task2 onceligi: %d\r\n", uxTaskPriorityGet(TaskHandle2));
	print_message(mymessage);

	while(1){

		if(buton_state == 1){

			buton_state = 0;

			p1 = uxTaskPriorityGet(TaskHandle1);
			p2 = uxTaskPriorityGet(TaskHandle2);

			vTaskPrioritySet(TaskHandle1,p2);
			vTaskPrioritySet(TaskHandle2,p1);
		}
	}

}
void Task2Handler(void *params){

	UBaseType_t p1,p2;

	sprintf(mymessage,"Task2 calisiyor\r\n");
	print_message(mymessage);

	sprintf(mymessage,"Task1 onceligi: %d\r\n", uxTaskPriorityGet(TaskHandle1));
	print_message(mymessage);

	sprintf(mymessage,"Task2 onceligi: %d\r\n", uxTaskPriorityGet(TaskHandle2));
	print_message(mymessage);

	while(1){
		if(buton_state == 1){

		buton_state = 0;

		p1 = uxTaskPriorityGet(TaskHandle1);
		p2 = uxTaskPriorityGet(TaskHandle2);

		vTaskPrioritySet(TaskHandle1,p2);
		vTaskPrioritySet(TaskHandle2,p1);
	}
}
}

void Sys_Config(){
	GPIO_Config();
	USART_Config();
	EXTI_Config();

}

void GPIO_Config(){


	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	GPIO_InitTypeDef GPIO_Init_Struct = {0};

	GPIO_Init_Struct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_Struct.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init_Struct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA,&GPIO_Init_Struct);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);

	GPIO_Init_Struct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_Struct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Init_Struct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init_Struct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);

	GPIO_Init(GPIOA,&GPIO_Init_Struct);
}

void USART_Config(){

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

	USART_InitTypeDef USART_Init_Struct = {0};

	USART_Init_Struct.USART_BaudRate = 9600;
	USART_Init_Struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init_Struct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init_Struct.USART_Parity = USART_Parity_No;
	USART_Init_Struct.USART_StopBits = USART_StopBits_1;
	USART_Init_Struct.USART_WordLength = USART_WordLength_8b;

	USART_Init(USART2,&USART_Init_Struct);

	USART_Cmd(USART2,ENABLE);

}

void EXTI_Config(){

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);

	EXTI_InitTypeDef EXTI_Init_Struct = {0};

	EXTI_Init_Struct.EXTI_Line = EXTI_Line0;
	EXTI_Init_Struct.EXTI_LineCmd = ENABLE;
	EXTI_Init_Struct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Init_Struct.EXTI_Trigger = EXTI_Trigger_Rising;

	EXTI_Init(&EXTI_Init_Struct);

	NVIC_SetPriority(EXTI0_IRQn,2);
	NVIC_EnableIRQ(EXTI0_IRQn);


}


void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}


uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
