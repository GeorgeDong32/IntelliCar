#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "Timer.h"

void LED_GPIO_Confing(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

int main(void)
{
    TimerBase_Config();
    LED_GPIO_Confing();
    GPIO_SetBits(GPIOA, GPIO_Pin_8);
    while (1)
    {
    }
}
