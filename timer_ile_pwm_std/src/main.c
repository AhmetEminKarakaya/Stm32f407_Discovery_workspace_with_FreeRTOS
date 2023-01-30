#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


GPIO_InitTypeDef 		GPIO_Init_struct;
TIM_TimeBaseInitTypeDef TIM_Init_struct;
TIM_OCInitTypeDef       TIM_OC_Init_struct;

void GPIO_Config(){

	RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIODEN,ENABLE);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);

	GPIO_Init_struct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init_struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_struct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init_struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init_struct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD,&GPIO_Init_struct);

}

void TIM_Config(){

	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM4EN,ENABLE);

	TIM_Init_struct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_Init_struct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_Init_struct.TIM_Period = 9999;
	TIM_Init_struct.TIM_Prescaler = 8399;
	TIM_Init_struct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM4,&TIM_Init_struct);

	TIM_Cmd(TIM4,ENABLE);

	TIM_OC_Init_struct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OC_Init_struct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC_Init_struct.TIM_OutputState =  ENABLE;


}

/*
 * Period = (Timer_Tick_Freq / PWM_Freq) - 1
 *
 * PWM_Freq = Timer_Tick_Freq / (Period + 1)
 *
 * Timer_Tick_Freq = Timer_CLK /(Prescaler + 1)
 *
 */


int main(void)
{

	GPIO_Config();
	TIM_Config();

  while (1)
  {
	  // PD12
	  TIM_OC_Init_struct.TIM_Pulse =9999;
	  TIM_OC1Init(TIM4,&TIM_OC_Init_struct);
	  TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);

	  // PD13
	  TIM_OC_Init_struct.TIM_Pulse =7499;
	  TIM_OC2Init(TIM4,&TIM_OC_Init_struct);
	  TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);

	  // PD14
	  TIM_OC_Init_struct.TIM_Pulse =4999;
	  TIM_OC3Init(TIM4,&TIM_OC_Init_struct);
	  TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);

	  // PD15
	  TIM_OC_Init_struct.TIM_Pulse =2499;
	  TIM_OC4Init(TIM4,&TIM_OC_Init_struct);
	  TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);

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
