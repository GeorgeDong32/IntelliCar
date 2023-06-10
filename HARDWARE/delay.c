#include "delay.h"

// 毫秒延迟
void delay_ms(uint32_t ms)
{
	uint32_t i;
	SysTick_Config(72000);
	for (i = 0; i < ms; i++)
	{
		while (!((SysTick->CTRL) & (1 << 16)))
			;
	}

	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

// 微秒延迟
void delay_us(uint32_t us)
{
	uint32_t i;
	SysTick_Config(72);
	for (i = 0; i < us; i++)
	{
		while (!((SysTick->CTRL) & (1 << 16)))
			;
	}

	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}
