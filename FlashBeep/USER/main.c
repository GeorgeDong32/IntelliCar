#include "stm32f10x.h"
#include "keysacn.h"
#include "delay.h"

int main(void)
{
	delay_init();
	KEY_Init();
	while (1)
	{
		keysacn();
	}
}
