#ifndef __SERVO_H
#define __SERVO_H
#include "stm32f10x.h"

void TIM5_PWM_Init(u16 arr, u16 psc);
void SetJointAngle(float angle);

#endif
