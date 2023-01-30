#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

/*
 * 				(period + 1) (prescaler + 1)
 *   saniye =   -----------------------------
 * 				         clock speed
 *
 *
 *
 */

int count = 0;


TIM_TimeBaseInitTypeDef TIM_Init_Struct;
GPIO_InitTypeDef GPIO_Init_Struct;


void Timer_Config(){

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_Init_Struct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_Init_Struct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_Init_Struct.TIM_Period = 3999;
	TIM_Init_Struct.TIM_Prescaler = 41999;
	TIM_Init_Struct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM2,&TIM_Init_Struct);

	TIM_Cmd(TIM2,ENABLE);

}


void GPIO_Config(){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

	GPIO_Init_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_Struct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init_Struct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD,&GPIO_Init_Struct);

}



int main(void)
{
	Timer_Config();
	GPIO_Config();


  while (1)
  {

	  count = TIM_GetCounter(TIM2);

	  if(count == 1999){
		  GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	  }
	  else if(count == 3999){
		  GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

	  }

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
