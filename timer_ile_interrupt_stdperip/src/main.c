#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


GPIO_InitTypeDef GPIO_Init_Struct;
TIM_TimeBaseInitTypeDef TIM_Init_Struct;
NVIC_InitTypeDef NVIC_Init_Struct;



void GPIO_Config(){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

	GPIO_Init_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_Struct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init_Struct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD,&GPIO_Init_Struct);
}

void TIM_Config(){

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

	TIM_Init_Struct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_Init_Struct.TIM_CounterMode =	TIM_CounterMode_Up;
	TIM_Init_Struct.TIM_Period = 1999;
	TIM_Init_Struct.TIM_Prescaler = 41999;
	TIM_Init_Struct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM3,&TIM_Init_Struct);

	TIM_Cmd(TIM3,ENABLE);

}

void NVIC_Config(){

	NVIC_Init_Struct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_Init_Struct.NVIC_IRQChannelCmd = ENABLE;

	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);

	NVIC_Init(&NVIC_Init_Struct);

}

void TIM3_IRQHandler(){

	GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);

}


int main(void)
{

	GPIO_Config();
	TIM_Config();
	NVIC_Config();



  while (1)
  {

  }
}


void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}


uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
