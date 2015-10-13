/*******************************************************************************
* 文件名		: main.c
********************************************************************************/

/* 头文件    ------------------------------------------------------------------*/


#include "led.h"

int main(void)
{
   
  	/* 设置系统时钟 */
  	RCC_Configuration();			

  	/* 设置GPIO端口 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	
	GPIO_Configuration();
	GPIO_SetBits(GPIOA , GPIO_Pin_4);	// PA.4输出高电平
	GPIO_SetBits(GPIOA , GPIO_Pin_5);	// PA.5输出高电平
	GPIO_SetBits(GPIOA , GPIO_Pin_6);	// PA.6输出高电平
	
	while(1);

}




