#include "stm32f10x.h" // Device header
#include "delay.h"
#include "motor.h"

int main(void)
{
	Motor_Init(7199, 0);
	while (1)
	{
		/*Dev Test Function*/ /*
		 car_control_test(0, 500);
		 car_brake(3000);
		 car_control_test(1, 500);
		 car_brake(4000);
		 */
							  /*Test Function*/

		car_forward(50, 500);
		car_brake(2000);
		car_back(50, 500);
		car_brake(2000);
		car_left(50, 500);
		car_brake(2000);
		car_right(50, 500);
		car_brake(2000);
		car_leftspin(50, 500);
		car_brake(2000);
		car_rightspin(50, 500);
		car_brake(4000);
	}
}
