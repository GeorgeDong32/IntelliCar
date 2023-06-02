#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Servo.h"

float Angle=0.0;
int main(void)
{
	Servo_Init();
	Angle=0;

	Angle = 0;
	while (1)
	{
		if (1)
		{
			Angle += 45;
			if (Angle > 180)
			{
				Angle = 0;
			}
		}
		Servo_SetAngle(Angle);
		Delay_ms(500);
	}
}
