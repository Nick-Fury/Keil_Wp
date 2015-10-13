/*******************************************************************************
* 文件名          : main.c
* 作者            : Nick.Lee
* 时间			  		: 18/09/2015
* 文件描述        : 主函数
********************************************************************************/

/* 头文件    ------------------------------------------------------------------*/

#include "stm32f10x.h"

/* 自定义同义关键字    --------------------------------------------------------*/

/* 自定义参数宏        --------------------------------------------------------*/

/* 自定义函数宏        --------------------------------------------------------*/

/* 自定义变量          --------------------------------------------------------*/

/* 自定义函数声明      --------------------------------------------------------*/

void GPIO_Configuration(void);



/*******************************************************************************
* 函数名				 : main
* 函数描述       : Main 函数
* 输入参数       : 无
* 输出结果       : 无
* 返回值         : 无
*******************************************************************************/

int main(void)
{
   
  	/* 设置系统时钟 */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); 			

  	/* 设置GPIO端口 */
  	GPIO_Configuration();
  
  	
		GPIO_SetBits(GPIOA , GPIO_Pin_4);         // PA.2输出高电平
		GPIO_SetBits(GPIOA , GPIO_Pin_5);		  // PA.3输出高电平
		GPIO_SetBits(GPIOA , GPIO_Pin_6);		  // PA.3输出高电平
		GPIO_SetBits(GPIOA , GPIO_Pin_7);		  // PA.3输出高电平

	while(1);

}



/*******************************************************************************
* 函数名  		: GPIO_Configuration
* 函数描述    	: 设置各GPIO端口功能
* 输入参数      : 无
* 输出结果      : 无
* 返回值        : 无
*******************************************************************************/

void GPIO_Configuration(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
 
  	/* 设置PA2,PA3口为推挽输出，最大翻转频率为50MHz*/
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
  	GPIO_Init(GPIOA , &GPIO_InitStructure);
    
}

