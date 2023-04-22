#include "stm32f10x.h"
#include "stm32f10x_it.h"

void LED_GPIO_Confing(void);

void TIM4_Init(void);

void TIME4_NVIC_Init(void);

void TIM4_PWM_Init(void);

void TIM4_OutPin_Init(void);

static u16 dir = 1;
static u32 pwm = 0;

int main(void)
{
    LED_GPIO_Confing();
    TIM4_Init();
    TIME4_NVIC_Init();
    TIM4_PWM_Init();
    TIM4_OutPin_Init();
    while (1)
    {
        if (dir == 1)
        {
            pwm++;
        }
        else
        {
            pwm--;
        }
        if (pwm > 300)
        {
            dir = 0;
        }
        if (pwm == 0)
        {
            dir = 1;
        }
        TIM_SetCompare2(TIM4, pwm);
    }
}

void TIM4_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); // 配置系统时钟

    // 初始化 TIM4 定时器
    // 慢但明显 200-1 7200-1; 快但不明显 100-1 7200-1
    TIM_TimeBaseStructure.TIM_Period = 100 - 1;                 // PWM时尽量为 n * 100 - 1
    TIM_TimeBaseStructure.TIM_Prescaler = 7200 - 1;             // 设置 TIM4 的预分频值 PSC 20KHz
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向下计数模式
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // 设置时钟分割
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);             // 根据 TIM_TimeBaseInitStruc 中指定的参数初始化 TIM4
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);                       // 清除溢出中断标志
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);                  // 使能 TIM4 中断

    TIM_Cmd(TIM4, ENABLE); // 使能 TIM4定时
}

void TIME4_NVIC_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 中断优先级 2 位

    // 设置系统中断管理参数,使能 TIM4 中断
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;           // TIM4 中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; // 抢占优先级 2（0~3），中断优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        // 子优先级 2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // 中断使能

    NVIC_Init(&NVIC_InitStructure); // 参数初始化 NVIC
}

void LED_GPIO_Confing(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOA, GPIO_Pin_5);
}

void TIM4_PWM_Init(void)
{
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; // PWM 模式 1
    TIM_OCInitStructure.TIM_Pulse = 300 - 1;          // 设置比较值
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
    // TIM_ARRPreloadConfig(TIM4, ENABLE);
}

void TIM4_OutPin_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}
