#include "stm32f10x.h"
#include "delay.h"
#include "motor.h"
#include "usart.h"
#include "remote.h"   
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
	 u8 key;
	 delay_init();
	 TIM4_PWM_Init(7199,0);  //��ʼ��PWM
	// NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2	  
	// uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600  
	 Remote_Init();			//������ճ�ʼ��	
   ZYSTM32_brake(500);	 
	 while(1)
		{  
		 	key=Remote_Scan();	
	//		printf("%d\n",key);
			switch(key)
			{    
				case 98:ZYSTM32_run(60,100);break;	    
				case 2:ZYSTM32_brake(100);break;		 	  
				case 194:ZYSTM32_Right(60,100);break;	   
				case 34:ZYSTM32_Left(60,100);break;		  
				case 224:ZYSTM32_Spin_Left(60,100);break;		  
				case 168:ZYSTM32_back(40,100);break;		   
				case 144:ZYSTM32_Spin_Right(60,100);break;		    
			}
				
		}
 }

