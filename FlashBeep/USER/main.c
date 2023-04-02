#include "stm32f10x.h"
#include "keysacn.h"
#include "delay.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB, ENABLE); // 使能PA,C,D端口时钟
	while (1)
	{
		keysacn();
	}
}
