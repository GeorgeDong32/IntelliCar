#ifndef __ULTRASONIC_H__
#define __ULTRASONIC_H__

#include "stm32f10x.h"
#include "delay.h"

#define ECHO_Reci GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)
#define TRIG_Send(a)                     \
    if (a)                               \
        GPIO_SetBits(GPIOC, GPIO_Pin_0); \
    else                                 \
        GPIO_ResetBits(GPIOC, GPIO_Pin_0)

void servo_config(void);

void HC_SR04Config(void);

void Open_TIM5(void);

void Close_TIM5(void);

void TIM5_IRQHandler(void);

int GetEcho_time(void);

float GetLength(void);

int front_scan(void);

int left_scan(void);

int right_scan(void);

#endif
