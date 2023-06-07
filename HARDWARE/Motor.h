#ifndef __MOTOR_H_
#define __MOTOR_H_

#include "stm32f10x.h"

void Car_Motor_Init(unsigned short arr, unsigned short psc);
void SetMotorSpeed(unsigned char ucChannel, signed char cSpeed);

void Car_forward(signed char speed, int time);
void Car_brake(int time);
void Car_left(signed char speed, int time);
void Car_leftSpin(signed char speed, int time);
void Car_right(signed char speed, int time);
void Car_rightSpin(signed char speed, int time);
void Car_back(signed char speed, int time);

#define LEFT_MOTOR_GO GPIO_Pin_7
#define LEFT_MOTOR_GO_GPIO GPIOB
#define LEFT_MOTOR_GO_SET GPIO_SetBits(LEFT_MOTOR_GO_GPIO, LEFT_MOTOR_GO)
#define LEFT_MOTOR_GO_RESET GPIO_ResetBits(LEFT_MOTOR_GO_GPIO, LEFT_MOTOR_GO)

#define LEFT_MOTOR_PWM GPIO_Pin_8
#define LEFT_MOTOR_PWM_GPIO GPIOB
#define LEFT_MOTOR_PWM_SET GPIO_SetBits(LEFT_MOTOR_PWM_GPIO, LEFT_MOTOR_PWM)
#define LEFT_MOTOR_PWM_RESET GPIO_ResetBits(LEFT_MOTOR_PWM_GPIO, LEFT_MOTOR_PWM)

#define RIGHT_MOTOR_GO GPIO_Pin_4
#define RIGHT_MOTOR_GPIO GPIOA
#define RIGHT_MOTOR_GO_SET GPIO_SetBits(RIGHT_MOTOR_GPIO, RIGHT_MOTOR_GO)
#define RIGHT_MOTOR_GO_RESET GPIO_ResetBits(RIGHT_MOTOR_GPIO, RIGHT_MOTOR_GO)

#define RIGHT_MOTOR_PWM GPIO_Pin_9
#define RIGHT_MOTOR_PWM_GPIO GPIOB
#define RIGHT_MOTOR_PWM_SET GPIO_SetBits(RIGHT_MOTOR_PWM_GPIO, RIGHT_MOTOR_PWM)
#define RIGHT_MOTOR_PWM_RESET GPIO_ResetBits(RIGHT_MOTOR_PWM_GPIO, RIGHT_MOTOR_PWM)

#endif
