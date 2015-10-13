/*******************************************************************************
* �ļ���          : main.c
* ����            : Losingamong
* ʱ��			  : 08/08/2008
* �ļ�����        : ������
********************************************************************************/

/* ͷ�ļ�    ------------------------------------------------------------------*/

#include "stm32f10x.h"

/* �Զ���ͬ��ؼ���    --------------------------------------------------------*/

/* �Զ��������        --------------------------------------------------------*/

/* �Զ��庯����        --------------------------------------------------------*/

/* �Զ������          --------------------------------------------------------*/

/* �Զ��庯������      --------------------------------------------------------*/

void RCC_Configuration(void);
void GPIO_Configuration(void);



/*******************************************************************************
* ������		 : main
* ��������       : Main ����
* �������       : ��
* ������       : ��
* ����ֵ         : ��
*******************************************************************************/

int main(void)
{
   
  	/* ����ϵͳʱ�� */
  	RCC_Configuration();			

  	/* ����GPIO�˿� */
  	GPIO_Configuration();
  
  	
	GPIO_SetBits(GPIOA , GPIO_Pin_4);         // PA.2����ߵ�ƽ
	GPIO_SetBits(GPIOA , GPIO_Pin_5);		  // PA.3����ߵ�ƽ
	GPIO_SetBits(GPIOA , GPIO_Pin_6);		  // PA.3����ߵ�ƽ
	while(1);

}



/*******************************************************************************
* ������	: RCC_Configuration
* ��������  : ����ϵͳ������ʱ��
* �������  : ��
* ������  : ��
* ����ֵ    : ��
*******************************************************************************/

void RCC_Configuration(void)
{
	/* ����ö�����ͱ��� HSEStartUpStatus */
	ErrorStatus HSEStartUpStatus;

  	/* ��λϵͳʱ������*/
  	RCC_DeInit();

  	/* ����HSE*/
  	RCC_HSEConfig(RCC_HSE_ON);

  	/* �ȴ�HSE�����ȶ�*/
  	HSEStartUpStatus = RCC_WaitForHSEStartUp();
	
	/* �ж�HSE���Ƿ���ɹ����������if()�ڲ� */
  	if(HSEStartUpStatus == SUCCESS)
  	{
    	/* ѡ��HCLK��AHB��ʱ��ԴΪSYSCLK 1��Ƶ */
    	RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    	/* ѡ��PCLK2ʱ��ԴΪ HCLK��AHB�� 1��Ƶ */
    	RCC_PCLK2Config(RCC_HCLK_Div1); 

    	/* ѡ��PCLK1ʱ��ԴΪ HCLK��AHB�� 2��Ƶ */
    	RCC_PCLK1Config(RCC_HCLK_Div2);

    	/* ����FLASH��ʱ������Ϊ2 */
    	FLASH_SetLatency(FLASH_Latency_2);
    	/* ʹ��FLASHԤȡ���� */
    	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    	/* ѡ�����໷��PLL��ʱ��ԴΪHSE 1��Ƶ����Ƶ��Ϊ9����PLL���Ƶ��Ϊ 8MHz * 9 = 72MHz */
    	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    	/* ʹ��PLL */ 
    	RCC_PLLCmd(ENABLE);

    	/* �ȴ�PLL����ȶ� */
    	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

    	/* ѡ��SYSCLKʱ��ԴΪPLL */
    	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    	/* �ȴ�PLL��ΪSYSCLKʱ��Դ */
    	while(RCC_GetSYSCLKSource() != 0x08);
  	}
   
  	/* ��APB2�����ϵ�GPIOAʱ��*/
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
}


/*******************************************************************************
* ������  		: GPIO_Configuration
* ��������    	: ���ø�GPIO�˿ڹ���
* �������      : ��
* ������      : ��
* ����ֵ        : ��
*******************************************************************************/

void GPIO_Configuration(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
 
  	/* ����PA2,PA3��Ϊ������������תƵ��Ϊ50MHz*/
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_Init(GPIOA , &GPIO_InitStructure);

    
}

