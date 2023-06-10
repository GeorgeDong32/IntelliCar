#include "ultrasonic.h"

uint16_t mscount = 0;

// 舵机初始化
void servo_config(void)
{
    GPIO_InitTypeDef GPIO_Motorinit;
    TIM_TimeBaseInitTypeDef TIM_Motorinit;
    TIM_OCInitTypeDef TIMPWM_Motorinit;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    GPIO_Motorinit.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Motorinit.GPIO_Pin = GPIO_Pin_0;
    GPIO_Motorinit.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_Motorinit);

    TIM_Motorinit.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_Motorinit.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_Motorinit.TIM_Period = 2000 - 1;
    TIM_Motorinit.TIM_Prescaler = 720 - 1;
    TIM_TimeBaseInit(TIM2, &TIM_Motorinit);

    TIMPWM_Motorinit.TIM_OCMode = TIM_OCMode_PWM1;
    TIMPWM_Motorinit.TIM_OutputState = TIM_OutputState_Enable;
    TIMPWM_Motorinit.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM2, &TIMPWM_Motorinit);
    TIM_CtrlPWMOutputs(TIM2, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
}

// 超声波模块初始化
void HC_SR04Config(void)
{
    GPIO_InitTypeDef GPIO_HCSR04init;
    TIM_TimeBaseInitTypeDef TIM_HCSR04init;
    NVIC_InitTypeDef NVIC_HCSR04init;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    GPIO_HCSR04init.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_HCSR04init.GPIO_Pin = GPIO_Pin_0;
    GPIO_HCSR04init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_HCSR04init);

    GPIO_HCSR04init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_HCSR04init.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOC, &GPIO_HCSR04init);

    TIM_HCSR04init.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_HCSR04init.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_HCSR04init.TIM_Period = 1000 - 1;
    TIM_HCSR04init.TIM_Prescaler = 72 - 1;

    TIM_TimeBaseInit(TIM5, &TIM_HCSR04init);
    TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);

    TIM_Cmd(TIM5, DISABLE);

    NVIC_HCSR04init.NVIC_IRQChannel = TIM5_IRQn;
    NVIC_HCSR04init.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_HCSR04init.NVIC_IRQChannelSubPriority = 0;
    NVIC_HCSR04init.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_HCSR04init);
}

// 打开定时器5
void Open_TIM5(void)
{
    TIM_SetCounter(TIM5, 0);
    mscount = 0;
    TIM_Cmd(TIM5, ENABLE);
}

// 关闭定时器5
void Close_TIM5(void)
{
    TIM_Cmd(TIM5, DISABLE);
}

// 超声波模块中断
void TIM5_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
        mscount++;
    }
}

// 超声波回应时间
int GetEcho_time(void)
{
    uint32_t t = 0;
    t = mscount * 1000;
    t += TIM_GetCounter(TIM5);
    TIM5->CNT = 0;
    delay_us(50);

    return t;
}

// 超声波测距实现
float GetLength(void)
{
    int i = 0;
    uint32_t t = 0;
    float length = 0;
    float sum = 0;

    while (i != 5)
    {
        TRIG_Send(1);
        delay_us(20);
        TRIG_Send(0);

        while (ECHO_Reci == 0)
            ;
        Open_TIM5();
        i = i + 1;

        while (ECHO_Reci == 1)
            ;

        Close_TIM5();
        t = GetEcho_time();
        length = ((float)t / 58.0);
        sum = sum + length;
    }
    length = sum / 5.0;
    return length;
}

// 小车前方距离测量
int front_scan(void)
{
    int pwmval = 150;
    TIM_SetCompare1(TIM2, pwmval);
    delay_ms(500);
    return GetLength();
}

// 小车左侧距离测量
int left_scan(void)
{
    int pwmval = 250;
    TIM_SetCompare1(TIM2, pwmval);
    delay_ms(500);
    return GetLength();
}

// 小车右侧距离测量
int right_scan(void)
{
    int pwmval = 50;
    TIM_SetCompare1(TIM2, pwmval);
    delay_ms(500);
    return GetLength();
}
