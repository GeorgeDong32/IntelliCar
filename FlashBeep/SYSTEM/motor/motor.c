#include "motor.h"
#include "Math.h"
#include "delay.h"
#include "stm32f10x.h"                  // Device header

signed short sPWMR,sPWML,dPWM;

//GPIO���ú���
/*void MotorGPIO_Configuration(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PA,PB�˿�ʱ��
	
	GPIO_InitStructure.GPIO_Pin = LEFT_MOTOR_GO;         //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_Init(LEFT_MOTOR_GO_GPIO, &GPIO_InitStructure);    
	
	GPIO_InitStructure.GPIO_Pin = LEFT_MOTOR_PWM;	
	GPIO_Init(LEFT_MOTOR_PWM_GPIO, &GPIO_InitStructure); 
	
	
 	GPIO_InitStructure.GPIO_Pin = RIGHT_MOTOR_PWM;	
	GPIO_Init(RIGHT_MOTOR_PWM_GPIO, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = RIGHT_MOTOR_GO;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	GPIO_Init(RIGHT_MOTOR_GPIO, &GPIO_InitStructure); 
	
}

void run()     //ǰ��
{
	RIGHT_MOTOR_GO_SET;
	RIGHT_MOTOR_PWM_RESET;//PB9
	
	LEFT_MOTOR_GO_SET;
	LEFT_MOTOR_PWM_RESET;//PB8
	
	
}
*/

void TIM4_PWM_Init(unsigned short arr,unsigned short psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);// 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB , ENABLE);  //ʹ��GPIO����ʱ��ʹ��   
	
  GPIO_InitStructure.GPIO_Pin = LEFT_MOTOR_GO;         //����������� PB7
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_Init(LEFT_MOTOR_GO_GPIO, &GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Pin = LEFT_MOTOR_PWM;         //����PWM���� PB8
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	   //�����������
	GPIO_Init(LEFT_MOTOR_PWM_GPIO, &GPIO_InitStructure);  
		
	
  GPIO_InitStructure.GPIO_Pin = RIGHT_MOTOR_GO;       //�ҵ���������  PA4
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	GPIO_Init(RIGHT_MOTOR_GPIO, &GPIO_InitStructure); 
	
	
	GPIO_InitStructure.GPIO_Pin = RIGHT_MOTOR_PWM;       //�ҵ��PWM����  PB9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	   //�����������
	GPIO_Init(RIGHT_MOTOR_PWM_GPIO, &GPIO_InitStructure);  
	
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	
	TIM_CtrlPWMOutputs(TIM4,ENABLE);	//MOE �����ʹ��	
  
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	 
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��
	
  TIM_ARRPreloadConfig(TIM4, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
 	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM1   
}

void SetMotorSpeed(unsigned char ucChannel,signed char cSpeed)
{
//		static short sMotorSpeed = 0;
		short sPWM;
//	  float fDir = 1;
	
		if (cSpeed>=100) cSpeed = 100;
	  if (cSpeed<=-100) cSpeed = -100;
	
   	sPWM = 7201 - fabs(cSpeed)*72;
	switch(ucChannel)
	{
		case 0://����
			TIM_SetCompare3(TIM4,sPWM);
			if (cSpeed>0) 
				RIGHT_MOTOR_GO_RESET;
			else if(cSpeed<0) 
				RIGHT_MOTOR_GO_SET;		
			break;
		case 1://����
		  TIM_SetCompare4(TIM4,sPWM); 
			if (cSpeed>0) 
				LEFT_MOTOR_GO_SET;
			else if (cSpeed<0)
				LEFT_MOTOR_GO_RESET;
			break;			
	}
}

//----------------------------------�˶�����--------------------------------
void ZYSTM32_run(signed char speed,int time)  //ǰ������
{
		  signed char f_speed = - speed;
	    SetMotorSpeed(1,f_speed);//����  //Ϊ����
			SetMotorSpeed(0,speed);//����   //Ϊ����
			delay_ms(time);                 //ʱ��Ϊ����

}

void ZYSTM32_brake(int time) //ɲ������
{
	  SetMotorSpeed(1,0);//����   //Ϊ0
	  SetMotorSpeed(0,0);//����   //Ϊ0
	  RIGHT_MOTOR_GO_RESET;
	  LEFT_MOTOR_GO_RESET;
		delay_ms(time);             //ʱ��Ϊ����  
}

void ZYSTM32_Left(signed char speed,int time) //��ת����
{
	  SetMotorSpeed(1,0);//����     //���ֲ���
	  SetMotorSpeed(0,speed);        //����Ϊ��
		delay_ms(time);                 //ʱ��Ϊ����  

}
void ZYSTM32_Spin_Left(signed char speed,int time) //����ת����
{
	  SetMotorSpeed(1,speed);//����     //����Ϊ��
	  SetMotorSpeed(0,speed);            //����Ϊ��
		delay_ms(time);                    //ʱ��Ϊ����  

}
void ZYSTM32_Right(signed char speed,int time)  //��ת����
{
	  signed char f_speed = - speed;
	  SetMotorSpeed(1,f_speed);//����     //����Ϊ��
	  SetMotorSpeed(0,0);                 //����Ϊ0
		delay_ms(time);                   //ʱ��Ϊ����  

}
void ZYSTM32_Spin_Right(signed char speed,int time) //����ת����
{
	  signed char f_speed = - speed;
	  SetMotorSpeed(1,f_speed);//����     //����Ϊ��
	  SetMotorSpeed(0,f_speed);            //����Ϊ��
		delay_ms(time);                    //ʱ��Ϊ����  

}
void ZYSTM32_back(signed char speed,int time) //���˺���
{
	  signed char f_speed = - speed;
	  SetMotorSpeed(1,speed);//����   //Ϊ����
	  SetMotorSpeed(0,f_speed);//���� //Ϊ����
		delay_ms(time);                 //ʱ��Ϊ����  

}
