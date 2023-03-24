#include "stm32f10x.h"
#include "delay.h"
#include "motor.h"
#include "keysacn.h"
/*
void ZYSTM32_run(int speed,int time);       //ǰ������
void ZYSTM32_brake(int time);               //ɲ������
void ZYSTM32_Left(int speed,int time);      //��ת����
void ZYSTM32_Spin_Left(int speed,int time); //����ת����
void ZYSTM32_Right(int speed,int time);     //��ת����
void ZYSTM32_Spin_Right(int speed,int time);//����ת����
void ZYSTM32_back(int speed,int time);      //���˺���

*/


 int main(void)
 {	
	 delay_init();
	 KEY_Init();
	 TIM4_PWM_Init(7199,0);  //��ʼ��PWM
	 ZYSTM32_brake(500);
		while(1)
		{  
		 ZYSTM32_brake(500);
		 keysacn();			
		 ZYSTM32_back(50,1000);//����1s
		 ZYSTM32_brake(500);//ֹͣ0.5S
     ZYSTM32_run(50,1000);//ǰ��1S
		 ZYSTM32_brake(500);//ֹͣ0.5S
     ZYSTM32_Left(50,1000);//��ת1S
     ZYSTM32_Right(50,1000);//��ת1S
  	 ZYSTM32_Spin_Right(50,1000);//������ת2S
     ZYSTM32_Spin_Left(50,1000);//������ת2S
     ZYSTM32_brake(500);//ֹͣ0.5S 		
		}
 }

