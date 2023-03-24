
#include "stm32f10x.h"
#define FlashTime 5000000
void Delay(u32 count)
{
	u32 i=0;
	for(;i<count;i++);
}

int main(void)
{	
	GPIO_InitTypeDef  GPIO_InitStructure;
			
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);	 //使能PA,PD端口时钟
	
	
	//初始化PA5时序指示灯
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				       //LED0-->PA.8 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA.8
	GPIO_SetBits(GPIOA,GPIO_Pin_5);						            //PA.8 输出高
	
	//初始化PA6蓝灯
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_6);
	
	//初始化PA4黄灯
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	
	//初始化PA2红灯
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
	
	//初始化PA3绿灯
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_3);

	//初始化GND接地线
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->PD.2 端口配置, 推挽输出
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GPIO_SetBits(GPIOD,GPIO_Pin_2); 						       //PD.2 输出高 	  
	while(1)
	{
		//Set亮灯，Reset灭灯
		//绿黄红蓝依次闪烁
		
		//初始化各灯
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
		GPIO_ResetBits(GPIOA,GPIO_Pin_3);
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		GPIO_ResetBits(GPIOA,GPIO_Pin_6);
		
		//闪烁程序
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		GPIO_SetBits(GPIOA,GPIO_Pin_3);
		Delay(FlashTime);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		Delay(FlashTime);
		
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		GPIO_ResetBits(GPIOA,GPIO_Pin_3);
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		Delay(FlashTime);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		Delay(FlashTime);
		
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
		Delay(FlashTime);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		Delay(FlashTime);
		
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
		GPIO_SetBits(GPIOA,GPIO_Pin_6);
		Delay(FlashTime);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		Delay(FlashTime);
	}
}

