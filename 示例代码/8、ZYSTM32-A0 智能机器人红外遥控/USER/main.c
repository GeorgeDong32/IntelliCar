#include "stm32f10x.h"
#include "delay.h"
#include "motor.h"
#include "usart.h"
#include "remote.h"   
/*
void ZYSTM32_run(int speed,int time);       //前进函数
void ZYSTM32_brake(int time);               //刹车函数
void ZYSTM32_Left(int speed,int time);      //左转函数
void ZYSTM32_Spin_Left(int speed,int time); //左旋转函数
void ZYSTM32_Right(int speed,int time);     //右转函数
void ZYSTM32_Spin_Right(int speed,int time);//右旋转函数
void ZYSTM32_back(int speed,int time);      //后退函数

*/


 int main(void)
 {	
	 u8 key;
	 delay_init();
	 TIM4_PWM_Init(7199,0);  //初始化PWM
	// NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2	  
	// uart_init(9600);	 	//串口初始化为9600  
	 Remote_Init();			//红外接收初始化	
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

