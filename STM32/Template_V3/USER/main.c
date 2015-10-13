/*******************************************************************************
* 文件名          : main.c
* 作者            : Losingamong
* 时间			  : 08/08/2008
* 文件描述        : 主函数
********************************************************************************/

/* 头文件    ------------------------------------------------------------------*/

#include "stm32f10x.h"

/* 自定义同义关键字    --------------------------------------------------------*/

/* 自定义参数宏        --------------------------------------------------------*/

/* 自定义函数宏        --------------------------------------------------------*/

/* 自定义变量          --------------------------------------------------------*/

/* 自定义函数声明      --------------------------------------------------------*/

void RCC_Configuration(void);
void GPIO_Configuration(void);



/*******************************************************************************
* 函数名		 : main
* 函数描述       : Main 函数
* 输入参数       : 无
* 输出结果       : 无
* 返回值         : 无
*******************************************************************************/

int main(void)
{
   
  	/* 设置系统时钟 */
  	RCC_Configuration();			

  	/* 设置GPIO端口 */
  	GPIO_Configuration();
  
  	
	GPIO_SetBits(GPIOA , GPIO_Pin_4);         // PA.2输出高电平
	GPIO_SetBits(GPIOA , GPIO_Pin_5);		  // PA.3输出高电平
	GPIO_SetBits(GPIOA , GPIO_Pin_6);		  // PA.3输出高电平
	while(1);

}



/*******************************************************************************
* 函数名	: RCC_Configuration
* 函数描述  : 设置系统各部分时钟
* 输入参数  : 无
* 输出结果  : 无
* 返回值    : 无
*******************************************************************************/

void RCC_Configuration(void)
{
	/* 定义枚举类型变量 HSEStartUpStatus */
	ErrorStatus HSEStartUpStatus;

  	/* 复位系统时钟设置*/
  	RCC_DeInit();

  	/* 开启HSE*/
  	RCC_HSEConfig(RCC_HSE_ON);

  	/* 等待HSE起振并稳定*/
  	HSEStartUpStatus = RCC_WaitForHSEStartUp();
	
	/* 判断HSE起是否振成功，是则进入if()内部 */
  	if(HSEStartUpStatus == SUCCESS)
  	{
    	/* 选择HCLK（AHB）时钟源为SYSCLK 1分频 */
    	RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    	/* 选择PCLK2时钟源为 HCLK（AHB） 1分频 */
    	RCC_PCLK2Config(RCC_HCLK_Div1); 

    	/* 选择PCLK1时钟源为 HCLK（AHB） 2分频 */
    	RCC_PCLK1Config(RCC_HCLK_Div2);

    	/* 设置FLASH延时周期数为2 */
    	FLASH_SetLatency(FLASH_Latency_2);
    	/* 使能FLASH预取缓存 */
    	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    	/* 选择锁相环（PLL）时钟源为HSE 1分频，倍频数为9，则PLL输出频率为 8MHz * 9 = 72MHz */
    	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    	/* 使能PLL */ 
    	RCC_PLLCmd(ENABLE);

    	/* 等待PLL输出稳定 */
    	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

    	/* 选择SYSCLK时钟源为PLL */
    	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    	/* 等待PLL成为SYSCLK时钟源 */
    	while(RCC_GetSYSCLKSource() != 0x08);
  	}
   
  	/* 打开APB2总线上的GPIOA时钟*/
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
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
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_Init(GPIOA , &GPIO_InitStructure);

    
}

