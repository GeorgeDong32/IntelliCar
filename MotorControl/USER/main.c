#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "motor.h"

 int main(void)
 {	
	  TIM4_PWM_Init(7199,0);  //��ʼ��PWM
		while(1)
		{  
		 ZYSTM32_back(50,500);//����1s
		 ZYSTM32_brake(1000);//ֹͣ0.5S
     /*ZYSTM32_run(50,500);//ǰ��1S
		 ZYSTM32_brake(1000);//ֹͣ0.5S
     ZYSTM32_Left(50,500);//��ת1S
		 ZYSTM32_brake(1000);//ֹͣ0.5S
     ZYSTM32_Right(50,500);//��ת1S
		 ZYSTM32_brake(1000);//ֹͣ0.5S
  	 ZYSTM32_Spin_Right(50,500);//������ת2S
		 ZYSTM32_brake(1000);//ֹͣ0.5S
     ZYSTM32_Spin_Left(50,500);//������ת2S
     ZYSTM32_brake(1000);//ֹͣ0.5S */		
		}
 }
