#include "stm32f10x.h"
#include "delay.h"
#include "motor.h"
#include "Beep.h"
#include "ultrasonic.h"

int main()
{
	/*Init*/
	int L_temp = 0;
	int R_temp = 0;
	int F_temp = 0;
	HC_SR04Config();
	servo_config();
	Motor_Init(7199, 0);
	car_brake(500);
	Beep_Init();
	TIM_SetCompare1(TIM2, 150);
	/*End Init*/
	delay_ms(500);
	while (1)
	{
		/*清零*/
		L_temp = 0;
		R_temp = 0;
		F_temp = 0;
		F_temp = front_scan();
		delay_ms(500);
		if (F_temp < 30 && F_temp > 0) // 前方被堵
		{
			/*停车检测*/
			car_brake(1000);
			L_temp = left_scan();
			delay_ms(500);
			R_temp = right_scan();
			delay_ms(500);
			TIM_SetCompare1(TIM2, 150);
			/*End 停车检测*/
			if ((L_temp < 25) && (R_temp < 25)) // 三侧被堵
			{
				BEEP_SET;
				delay_ms(3000);
				BEEP_RESET;
				if (L_temp >= R_temp)
					car_left(40, 1700);
				else
					car_right(40, 1700);
			}
			else if (L_temp > R_temp) // 右侧被堵
			{
				car_left(40, 1200);
				car_brake(500);
			}
			else // 左侧被堵
			{
				car_right(40, 1200);
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
