
#include "stm32f10x.h"
void Delay(u32 count)
{
	u32 i = 0;
	for (; i < count; i++)
	{
	}
}

int main(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	u32 FlashTime1 = 5000000;

	u32 FlashTime2 = 1000000;

	u32 i = 0;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD, ENABLE); // 使能PA,PD端口时钟

	// 初始化PA5指示灯
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;		  // LED0-->PA.5端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);			  // 根据设定参数初始化GPIOA.5
	GPIO_SetBits(GPIOA, GPIO_Pin_5);				  // PA.5 输出高

	// 初始化PA6红灯
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_6);

	// 初始化PA4绿灯
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);

	// 初始化PA2蓝灯
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_2);

	// 初始化PA3黄灯
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_3);

	// 初始化GND接地引脚
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; // LED1-->PD.2 端口配置
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  // 根据设定参数初始化GPIOD.2
	GPIO_SetBits(GPIOD, GPIO_Pin_2);		  // PD.2 输出高

	for (; i < 3; i++)
	{
		// 红绿蓝黄依次点灯

		// 初始化所有灯
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		GPIO_ResetBits(GPIOA, GPIO_Pin_6);

		// 普通点灯
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		GPIO_SetBits(GPIOA, GPIO_Pin_6);
		Delay(FlashTime1);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		Delay(FlashTime1);

		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		GPIO_ResetBits(GPIOA, GPIO_Pin_6);
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
		Delay(FlashTime1);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		Delay(FlashTime1);

		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
		Delay(FlashTime1);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		Delay(FlashTime1);

		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		GPIO_SetBits(GPIOA, GPIO_Pin_3);
		Delay(FlashTime1);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		Delay(FlashTime1);
	}

	// 初始化所有灯
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	GPIO_ResetBits(GPIOA, GPIO_Pin_6);

	for (; i < 10; i++)
	{
		// 跑马灯
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		GPIO_SetBits(GPIOA, GPIO_Pin_6);
		Delay(FlashTime2);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		Delay(FlashTime2);

		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		GPIO_ResetBits(GPIOA, GPIO_Pin_6);
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
		Delay(FlashTime2);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		Delay(FlashTime2);

		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
		Delay(FlashTime2);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		Delay(FlashTime2);

		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		GPIO_SetBits(GPIOA, GPIO_Pin_3);
		Delay(FlashTime2);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		Delay(FlashTime2);

		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
		Delay(FlashTime2);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		Delay(FlashTime2);

		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
		Delay(FlashTime2);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		Delay(FlashTime2);
	}

	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	GPIO_ResetBits(GPIOA, GPIO_Pin_6);
}
