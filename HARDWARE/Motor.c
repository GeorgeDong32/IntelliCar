#include "motor.h"
#include "Math.h"
#include "delay.h"
#include "stm32f10x.h"

signed short sPWMR, sPWML, dPWM;

void Car_Motor_Init(unsigned short arr, unsigned short psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = LEFT_MOTOR_GO;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(LEFT_MOTOR_GO_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LEFT_MOTOR_PWM;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(LEFT_MOTOR_PWM_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = RIGHT_MOTOR_GO;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(RIGHT_MOTOR_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = RIGHT_MOTOR_PWM;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(RIGHT_MOTOR_PWM_GPIO, &GPIO_InitStructure);

	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);

	TIM_CtrlPWMOutputs(TIM4, ENABLE);

	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM4, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
}

void SetMotorSpeed(unsigned char ucChannel, signed char cSpeed)
{
	short sPWM;

	if (cSpeed >= 100)
		cSpeed = 100;
	if (cSpeed <= -100)
		cSpeed = -100;

	sPWM = 7201 - fabs(cSpeed) * 72;
	switch (ucChannel)
	{
	case 0:
		TIM_SetCompare3(TIM4, sPWM);
		if (cSpeed > 0)
			RIGHT_MOTOR_GO_RESET;
		else if (cSpeed < 0)
			RIGHT_MOTOR_GO_SET;
		break;
	case 1:
		TIM_SetCompare4(TIM4, sPWM);
		if (cSpeed > 0)
			LEFT_MOTOR_GO_SET;
		else if (cSpeed < 0)
			LEFT_MOTOR_GO_RESET;
		break;
	}
}

void Car_forward(signed char speed, int time)
{
	signed char f_speed = -speed;
	SetMotorSpeed(1, f_speed);
	SetMotorSpeed(0, speed);
	delay_ms(time);
}

void Car_brake(int time)
{
	SetMotorSpeed(1, 0);
	SetMotorSpeed(0, 0);
	RIGHT_MOTOR_GO_RESET;
	LEFT_MOTOR_GO_RESET;
	delay_ms(time);
}

void Car_left(signed char speed, int time)
{
	SetMotorSpeed(1, 0);
	SetMotorSpeed(0, speed);
	delay_ms(time);
}
void Car_leftSpin(signed char speed, int time)
{
	SetMotorSpeed(1, speed);
	SetMotorSpeed(0, speed);
	delay_ms(time);
}
void Car_right(signed char speed, int time)
{
	signed char f_speed = -speed;
	SetMotorSpeed(1, f_speed);
	SetMotorSpeed(0, 0);
	delay_ms(time);
}
void Car_rightSpin(signed char speed, int time)
{
	signed char f_speed = -speed;
	SetMotorSpeed(1, f_speed);
	SetMotorSpeed(0, f_speed);
	delay_ms(time);
}
void Car_back(signed char speed, int time)
{
	signed char f_speed = -speed;
	SetMotorSpeed(1, speed);
	SetMotorSpeed(0, f_speed);
	delay_ms(time);
}
