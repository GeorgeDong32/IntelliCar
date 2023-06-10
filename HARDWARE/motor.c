#include "stm32f10x.h"
#include "motor.h"
#include "Math.h"
#include "delay.h"

signed short sPWMR, sPWML, dPWM;

void Motor_Init(unsigned short arr, unsigned short psc)
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
	case 0: // right
		TIM_SetCompare4(TIM4, sPWM);
		if (cSpeed >= 0)
			RIGHT_MOTOR_GO_RESET;
		else if (cSpeed < 0)
			RIGHT_MOTOR_GO_SET;
		break;
	case 1: // left
		TIM_SetCompare3(TIM4, sPWM);
		if (cSpeed > 0)
			LEFT_MOTOR_GO_SET;
		else if (cSpeed <= 0)
			LEFT_MOTOR_GO_RESET;
		break;
	}
}

void car_forward(signed char speed, int time) // 小车前进
{
	signed char f_speed = -speed;
	SetMotorSpeed(1, f_speed);
	SetMotorSpeed(0, speed);
	delay_ms(time);
}

void car_brake(int time) // 小车刹车
{
	SetMotorSpeed(1, 0);
	SetMotorSpeed(0, 0);
	RIGHT_MOTOR_GO_RESET;
	LEFT_MOTOR_GO_RESET;
	delay_ms(time);
}

void car_left(signed char speed, int time) // 小车左转
{
	SetMotorSpeed(1, 0);
	SetMotorSpeed(0, speed);
	delay_ms(time);
}

void car_leftspin(signed char speed, int time) // 小车左旋转
{
	SetMotorSpeed(1, speed);
	SetMotorSpeed(0, speed);
	delay_ms(time);
}

void car_right(signed char speed, int time) // 小车右转
{
	signed char f_speed = -speed;
	SetMotorSpeed(1, f_speed);
	SetMotorSpeed(0, 0);
	delay_ms(time);
}

void car_rightspin(signed char speed, int time) // 小车右旋转
{
	signed char f_speed = -speed;
	SetMotorSpeed(1, f_speed);
	SetMotorSpeed(0, f_speed);
	delay_ms(time);
}

void car_back(signed char speed, int time) // 小车后退
{
	signed char f_speed = -speed;
	SetMotorSpeed(0, f_speed);
	SetMotorSpeed(1, speed);
	delay_ms(time);
}

/*Test Function*/
void car_control_test(char mode, int time)
{
	signed char speed = 50;
	signed char f_speed = -50;
	switch (mode)
	{
	case 0:
		SetMotorSpeed(0, speed);
		SetMotorSpeed(1, 0);
		delay_ms(time);
		SetMotorSpeed(0, f_speed);
		SetMotorSpeed(1, 0);
		delay_ms(time);
		break;
	case 1:
		SetMotorSpeed(1, speed);
		SetMotorSpeed(0, 0);
		delay_ms(time);
		SetMotorSpeed(1, (-50));
		SetMotorSpeed(0, 0);
		delay_ms(time);
		break;
	default:
		break;
	}
}
