#include "IRAvoid.h"
#include "delay.h"
#include "motor.h"
#include "keysacn.h"
#include "stm32f10x.h"

void IRAvoidInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = AVOID_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(AVOID_PIN_GPIO, &GPIO_InitStructure);
}

void AVoidRun(void)
{
	if (AVOID_IO == BARRIER_N)
	{
		Car_forward(50, 10);
		BEEP_RESET;
		LED_D3_RESET;
	}
	else
	{
		BEEP_SET;
		LED_D3_SET;
		Car_brake(300);
		Car_back(50, 400);
		Car_left(50, 500);
	}
}
