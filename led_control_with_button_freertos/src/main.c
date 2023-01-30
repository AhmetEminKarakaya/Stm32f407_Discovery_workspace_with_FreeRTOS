#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

void SetupConfig();
void GPIO_InputConfig();
void GPIO_OutputConfig();


TaskHandle_t myButtonTaskHandle = NULL;
TaskHandle_t myledTaskHandle = NULL;

void readButtonstateTask(void *params);
void ledTask(void *params);

uint8_t buttoncount = 0;

int main(void)
{
	RCC_DeInit();

	SystemCoreClockUpdate();

	SetupConfig();

	xTaskCreate(readButtonstateTask,"Button Okuma Görevi",configMINIMAL_STACK_SIZE,
			NULL,3,&myButtonTaskHandle);
	xTaskCreate(ledTask,"Led Kontrol Görevi",configMINIMAL_STACK_SIZE,
			NULL,3,&myledTaskHandle);

	vTaskStartScheduler();

  while (1)
  {

  }
}

void readButtonstateTask(void *params){

	while(1){

		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == Bit_SET){
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == Bit_SET);
			buttoncount++;
		}
		if(buttoncount == 5){
			buttoncount = 0;
		}
	}
}
void ledTask(void *params){

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

void SetupConfig(){
	GPIO_InputConfig();
	GPIO_OutputConfig();
}


void GPIO_InputConfig(){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA,&GPIO_InitStruct);

}
void GPIO_OutputConfig(){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD,&GPIO_InitStruct);
}





void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
