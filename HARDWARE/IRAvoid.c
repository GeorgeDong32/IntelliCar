#include "IRAvoid.h"
#include "delay.h"
#include "motor.h"
#include "keysacn.h"
#include "stm32f10x.h"                  // Device header


void IRAvoidInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
	GPIO_InitStructure.GPIO_Pin = AVOID_PIN;//配置使能GPIO管脚 PB1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//配置GPIO模式,输入上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//配置GPIO端口速度
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
	   ZYSTM32_brake(300);//停止300MS
		 ZYSTM32_back(50,400);//后退400MS
		 ZYSTM32_Left(50,500);//左转500MS
				
	}
	
}
