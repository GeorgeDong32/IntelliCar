#include "stm32f10x.h"
#include "delay.h"

void MYTIM4_Init(void);

int main(void)
{
    MYTIM4_Init();
}

void MYTIM4_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);      // 中断优先级 2 位
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); // 配置系统时钟
    // 初始化 TIM4 ms 定时
    TIM_TimeBaseStructure.TIM_Period = 19999;                     // 设置在下一个更新事件装入活动的自动重装载寄存器ARR 的值, 计数值 20000 TIM_TimeBaseStructure.TIM_Prescaler = 3599; // 设置 TIM4 的预分频值 PSC 20KHz
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down; // 向下计数模式
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;       // 设置时钟分割
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);               // 根据 TIM_TimeBaseInitStruc 中指定的参数初始化 TIM4
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);                         // 清除溢出中断标志
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);                    // 使能 TIM4 中断
    // 设置系统中断管理参数,使能 TIM4 中断
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;           // TIM4 中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; // 抢占优先级 2（0~3），中断优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        // 子优先级 2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // 中断使能
    NVIC_Init(&NVIC_InitStructure);                           // 参数初始化 NVIC
    TIM_Cmd(TIM4, ENABLE);                                    // 使能 TIM4定时
}