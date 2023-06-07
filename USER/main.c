#include "stm32f10x.h"
#include "delay.h"
#include "motor.h"
#include "keysacn.h"
#include "IRSEARCH.h"
#include "IRAvoid.h"
#include "usart.h"
#include "UltrasonicWave.h"
#include "timer.h"
#include "Servo.h"

int front_detection(void);
int left_detection(void);
int right_detection(void);

int main(void)
{
	// Start Init Zone
	int Q_temp, L_temp, R_temp;
	delay_init();
	KEY_Init();
	IRSearchInit();
	IRAvoidInit();
	Timerx_Init(5000, 7199);
	UltrasonicWave_Configuration();
	uart_init(115200);
	Car_Motor_Init(7199, 0);
	TIM5_PWM_Init(9999, 143);
	Car_brake(500);
	keysacn();
	// End Init Zone

	while (1)
	{
		Q_temp = front_detection();
		if (Q_temp < 60 && Q_temp > 0) // 前方被挡
		{
			Car_brake(500);
			Car_back(60, 500);
			Car_brake(1000);

			L_temp = left_detection();
			delay_ms(500);
			R_temp = right_detection();
			delay_ms(500);
			// 所有方向被挡
			if ((L_temp < 60) && (R_temp < 60))
			{
				Car_leftSpin(60, 500);
			}
			// 右侧被挡
			else if (L_temp > R_temp)
			{
				Car_left(60, 700);
				Car_brake(500);
			}
			// 左侧被挡
			else
			{
				Car_right(60, 700);
				Car_brake(500);
			}
		}
		else
		{
			Car_forward(60, 10);
		}
	}
}

int front_detection()
{
	SetJointAngle(90);
	delay_ms(100);
	return UltrasonicWave_StartMeasure();
}

int left_detection()
{
	SetJointAngle(175);
	delay_ms(300);
	return UltrasonicWave_StartMeasure();
}

int right_detection()
{
	SetJointAngle(5);
	delay_ms(300);
	return UltrasonicWave_StartMeasure();
}
