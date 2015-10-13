#include "stm32f10x.h"
#include "delay.h"



uint16_t led_flag = 0;

/************************************************
void My_USART1_Init(void)
************************************************/
void My_USART1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStrue;
	USART_InitTypeDef USART_InitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//①开启GPIO时钟，GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//开启外设时钟,USART1
	
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
  GPIO_Init(GPIOA,&GPIO_InitStrue);//②初始化GPIO
	
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
  GPIO_Init(GPIOA,&GPIO_InitStrue);//②初始化GPIO
	
	USART_InitStrue.USART_BaudRate=115200;
	USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStrue.USART_Parity=USART_Parity_No;
	USART_InitStrue.USART_StopBits=USART_StopBits_1;
	USART_InitStrue.USART_WordLength=USART_WordLength_8b;
	
	USART_Init(USART1,&USART_InitStrue);//③初始化外设USART1
	
	USART_Cmd(USART1,ENABLE);//④使能USART1
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//采用中断接受，开启接收中断
	
	NVIC_InitStrue.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStrue);
	

}

void My_LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStrue;
	
	GPIO_InitStrue.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
  GPIO_InitStrue.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStrue.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA , &GPIO_InitStrue);	
}
void USART1_IRQHandler(void)
{
	 
	 u8 res;
	 if(USART_GetITStatus(USART1,USART_IT_RXNE))
 {
     res= USART_ReceiveData(USART1); 
		 res += 1;
     USART_SendData(USART1,res); 
		 led_flag= !led_flag; 
 }		
}
 
 int main(void)
 {
	 uint16_t dat=5;
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	 My_USART1_Init();
	 My_LED_Init();
	 delay_init();	 

	 while(1)
	 { 
		 if(led_flag == 0){

			GPIO_SetBits(GPIOA , GPIO_Pin_4);
			GPIO_ResetBits(GPIOA,GPIO_Pin_5);

		 }

	 	 if(led_flag == 1){
			GPIO_ResetBits(GPIOA,GPIO_Pin_4);
			GPIO_SetBits(GPIOA , GPIO_Pin_5);
		 }
		 delay_ms(100);
	 }
	 
 }
