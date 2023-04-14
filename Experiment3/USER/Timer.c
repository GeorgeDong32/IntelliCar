#include "Timer.h"

void TimerBase_Config(void)
{
    TIM_TimeBaseInitTypeDef TimerBaseInitStructure;
    NVIC_InitTypeDef NVICInitStructure;
    // 开时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    // 配置定时器结构体
    TimerBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TimerBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TimerBaseInitStructure.TIM_Period = 10000;
    TimerBaseInitStructure.TIM_Prescaler = 7200;
    TIM_TimeBaseInit(TIM4, &TimerBaseInitStructure);
    // 清空标志位
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);
    // 开启定时器中断
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    // 使能定时器
    TIM_Cmd(TIM4, ENABLE);
    // 配置NVIC结构体
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVICInitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVICInitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVICInitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVICInitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVICInitStructure);
}
