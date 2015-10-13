#include "stm32f10x_exti.h"

#include "exit.h"
#include "key.h"

void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTIX_InitStructure;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);			//1、使能复用时钟
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource13);
	
	EXTIX_InitStructure.EXTI_Line = EXTI_Line13;
	EXTIX_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTIX_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTIX_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTIX_InitStructure);
	
	NVIC_InitStruct.
	
}


