#include "stm32f10x.h"
#include "delay.h"
#include "motor.h"
#include "Beep.h"
#include "ultrasonic.h"

int main()
{
	int L_temp = 0;
	int R_temp = 0;
	int F_temp = 0;
	HC_SR04Config();
	servo_config();
	Motor_Init(7199, 0);
	car_brake(500);
	Beep_Init();
	TIM_SetCompare1(TIM2, 150);
	delay_ms(500);
	while (1)
	{
		L_temp = 0;
		R_temp = 0;
		F_temp = 0;
		F_temp = front_scan();
		delay_ms(500);
		if (F_temp < 25 && F_temp > 0)
		{
			car_brake(500);
			car_back(10, 200);
			car_brake(1000);
			L_temp = left_scan();
			delay_ms(500);
			R_temp = right_scan();
			delay_ms(500);
			TIM_SetCompare1(TIM2, 150);
			if ((L_temp < 20) && (R_temp < 20))
			{
				BEEP_SET;
				delay_ms(3000);
				BEEP_RESET;
				car_leftspin(40, 500);
			}
			else if (L_temp > R_temp)
			{
				car_left(60, 680);
				car_brake(500);
			}
			else
			{
				car_right(60, 630);
				car_brake(500);
			}
		}
		else
		{
			TIM_SetCompare1(TIM2, 150);
			car_forward(40, 10);
		}
	}
}
