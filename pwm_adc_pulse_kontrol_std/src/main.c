#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_Init_Struct;
TIM_TimeBaseInitTypeDef TIM_Init_Struct;
TIM_OCInitTypeDef TIMOC_Init_Struct;
ADC_InitTypeDef ADC_Init_Struct;
ADC_CommonInitTypeDef ADC_Common_Init_Struct;

uint16_t adc_value;
uint8_t pwm_value = 0;

uint8_t map(uint32_t A, uint32_t B, uint32_t C, uint32_t D, uint32_t E){

	return (A * E) / C;
}


void GPIO_Config(){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);

	GPIO_Init_Struct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_Struct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init_Struct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD,&GPIO_Init_Struct);

	GPIO_Init_Struct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_Init_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_Struct.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init_Struct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA,&GPIO_Init_Struct);

}

void TIM_Config(){

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

	TIM_Init_Struct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_Init_Struct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_Init_Struct.TIM_Period = 99;
	TIM_Init_Struct.TIM_Prescaler = 83;
	TIM_Init_Struct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM4,&TIM_Init_Struct);

	TIM_Cmd(TIM4,ENABLE);

	TIMOC_Init_Struct.TIM_OCMode = TIM_OCMode_PWM1;
	TIMOC_Init_Struct.TIM_OutputState = ENABLE;
	TIMOC_Init_Struct.TIM_OCPolarity = TIM_OCPolarity_High;


}

void ADC_Config(){

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);

	ADC_Common_Init_Struct.ADC_Mode = ADC_Mode_Independent;
	ADC_Common_Init_Struct.ADC_Prescaler = ADC_Prescaler_Div4;

	ADC_CommonInit(&ADC_Common_Init_Struct);

	ADC_Init_Struct.ADC_Resolution = ADC_Resolution_12b;

	ADC_Init(ADC1,&ADC_Init_Struct);

	ADC_Cmd(ADC1, ENABLE);
}


uint16_t Read_ADC(){

	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_56Cycles);

	ADC_SoftwareStartConv(ADC1);

	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);

	return ADC_GetConversionValue(ADC1);

}

int main(void)
{

	GPIO_Config();
	TIM_Config();
	ADC_Config();
  while (1)
  {
	  adc_value = Read_ADC();
	  pwm_value = map(adc_value,0,4095,0,99);

	  TIMOC_Init_Struct.TIM_Pulse = pwm_value;
	  TIM_OC1Init(TIM4,&TIMOC_Init_Struct);
	  TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);

	  TIMOC_Init_Struct.TIM_Pulse = pwm_value;
	  TIM_OC2Init(TIM4,&TIMOC_Init_Struct);
	  TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);

	  TIMOC_Init_Struct.TIM_Pulse = pwm_value;
	  TIM_OC3Init(TIM4,&TIMOC_Init_Struct);
	  TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);

	  TIMOC_Init_Struct.TIM_Pulse = pwm_value;
	  TIM_OC4Init(TIM4,&TIMOC_Init_Struct);
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
