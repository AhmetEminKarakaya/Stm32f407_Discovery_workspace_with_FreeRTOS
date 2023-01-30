#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

void SetupConfig();
void GPIO_Output_Config();
void GPIO_Input_Config();

uint8_t buttoncount;

TaskHandle_t myled = NULL;


void Led_Task(void * param);

void ButtonHandler(void);

void EXTI0_IRQHandler(void){

	EXTI_ClearITPendingBit(EXTI_Line0);

	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == Bit_SET){

		ButtonHandler();
	}

}


int main(void)
{

	RCC_DeInit();

	SystemCoreClockUpdate();

	SetupConfig();

	xTaskCreate(Led_Task,"Led yakma",configMINIMAL_STACK_SIZE,
				NULL,3,&myled);

	vTaskStartScheduler();


  while (1)
  {

  }
}

void Led_Task(void * param){
	while(1){
		if(buttoncount == 0){
				GPIO_ResetBits(GPIOD,GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

			}
			else if(buttoncount == 1){
				GPIO_ToggleBits(GPIOD,GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
				vTaskDelay(1000);
			}
			else if(buttoncount == 2){
				GPIO_ToggleBits(GPIOD,GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
				vTaskDelay(750);
			}
			else if(buttoncount == 3){
				GPIO_ToggleBits(GPIOD,GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
				vTaskDelay(500);
			}

			else if(buttoncount == 4){
				GPIO_ToggleBits(GPIOD,GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
				vTaskDelay(250);
			}

	}
}

void ButtonHandler(void){

	buttoncount++;

	if(buttoncount == 5){
		buttoncount = 0;
	}

}

void SetupConfig(){
	GPIO_Output_Config();
	GPIO_Input_Config();

}
void GPIO_Output_Config(){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	EXTI_InitTypeDef EXTI_InitStruct = {0};

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD,&GPIO_InitStruct);

	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;

	EXTI_Init(&EXTI_InitStruct);

	NVIC_SetPriority(EXTI0_IRQn,2);
	NVIC_EnableIRQ(EXTI0_IRQn);

}
void GPIO_Input_Config(){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA,&GPIO_InitStruct);


}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}


uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
