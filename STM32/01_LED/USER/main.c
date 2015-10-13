/*******************************************************************************
* �ļ���		: main.c
********************************************************************************/

/* ͷ�ļ�    ------------------------------------------------------------------*/


#include "led.h"

int main(void)
{
   
  	/* ����ϵͳʱ�� */
  	RCC_Configuration();			

  	/* ����GPIO�˿� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	
	GPIO_Configuration();
	GPIO_SetBits(GPIOA , GPIO_Pin_4);	// PA.4����ߵ�ƽ
	GPIO_SetBits(GPIOA , GPIO_Pin_5);	// PA.5����ߵ�ƽ
	GPIO_SetBits(GPIOA , GPIO_Pin_6);	// PA.6����ߵ�ƽ
	
	while(1);

}



