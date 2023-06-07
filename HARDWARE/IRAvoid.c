#include "IRAvoid.h"
#include "delay.h"
#include "motor.h"
#include "keysacn.h"
#include "stm32f10x.h"                  // Device header


void IRAvoidInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
	GPIO_InitStructure.GPIO_Pin = AVOID_PIN;//����ʹ��GPIO�ܽ� PB1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//����GPIOģʽ,��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����GPIO�˿��ٶ�
	GPIO_Init(AVOID_PIN_GPIO , &GPIO_InitStructure); 
}


void AVoidRun(void)
{
	if(AVOID_IO == BARRIER_N )
	{
		 ZYSTM32_run(50,10);
		 BEEP_RESET;
     LED_D3_RESET;		
	}
	else
	{
		 BEEP_SET;
     LED_D3_SET;	
	   ZYSTM32_brake(300);//ֹͣ300MS
		 ZYSTM32_back(50,400);//����400MS
		 ZYSTM32_Left(50,500);//��ת500MS
				
	}
	
}
