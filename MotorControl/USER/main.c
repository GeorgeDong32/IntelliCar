#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "motor.h"

 int main(void)
 {	
	  TIM4_PWM_Init(7199,0);  //初始化PWM
		while(1)
		{  
		 ZYSTM32_back(50,500);//后退1s
		 ZYSTM32_brake(1000);//停止0.5S
     /*ZYSTM32_run(50,500);//前进1S
		 ZYSTM32_brake(1000);//停止0.5S
     ZYSTM32_Left(50,500);//左转1S
		 ZYSTM32_brake(1000);//停止0.5S
     ZYSTM32_Right(50,500);//右转1S
		 ZYSTM32_brake(1000);//停止0.5S
  	 ZYSTM32_Spin_Right(50,500);//向右旋转2S
		 ZYSTM32_brake(1000);//停止0.5S
     ZYSTM32_Spin_Left(50,500);//向左旋转2S
     ZYSTM32_brake(1000);//停止0.5S */		
		}
 }
