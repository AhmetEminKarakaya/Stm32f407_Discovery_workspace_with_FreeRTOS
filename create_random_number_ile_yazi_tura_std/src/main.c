#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint32_t myRandomNumber;
uint32_t count,yazi,tura,oran;

void RNG_Config(){

	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG,ENABLE);

	RNG_Cmd(ENABLE);

}

void Delay(uint32_t time){

	while(time--);
}


int main(void)
{
  RNG_Config();

  while (1)
  {
	  myRandomNumber = RNG_GetRandomNumber();
	  Delay(10);

	  count++;

	  if(count <= 10000000){

		  if(myRandomNumber < 2147483648){
			  yazi++;
		  }
		  else{
			  tura++;
		  }

	  }
	  else{
		  oran = (float)yazi/tura;
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
