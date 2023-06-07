#include "motor.h"
#include "Math.h"
#include "delay.h"
#include "stm32f10x.h"                  // Device header

signed short sPWMR,sPWML,dPWM;

//GPIO配置函数
/*void MotorGPIO_Configuration(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);	 //使能PA,PB端口时钟
	
	GPIO_InitStructure.GPIO_Pin = LEFT_MOTOR_GO;         //左电机方向控制
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

void run()     //前进
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
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB , ENABLE);  //使能GPIO外设时钟使能   
	
  GPIO_InitStructure.GPIO_Pin = LEFT_MOTOR_GO;         //左电机方向控制 PB7
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_Init(LEFT_MOTOR_GO_GPIO, &GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Pin = LEFT_MOTOR_PWM;         //左电机PWM控制 PB8
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	   //复用推挽输出
	GPIO_Init(LEFT_MOTOR_PWM_GPIO, &GPIO_InitStructure);  
		
	
  GPIO_InitStructure.GPIO_Pin = RIGHT_MOTOR_GO;       //右电机方向控制  PA4
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	GPIO_Init(RIGHT_MOTOR_GPIO, &GPIO_InitStructure); 
	
	
	GPIO_InitStructure.GPIO_Pin = RIGHT_MOTOR_PWM;       //右电机PWM控制  PB9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	   //复用推挽输出
	GPIO_Init(RIGHT_MOTOR_PWM_GPIO, &GPIO_InitStructure);  
	
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	
	TIM_CtrlPWMOutputs(TIM4,ENABLE);	//MOE 主输出使能	
  
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH1预装载使能	 
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH1预装载使能
	
  TIM_ARRPreloadConfig(TIM4, ENABLE); //使能TIMx在ARR上的预装载寄存器
 	TIM_Cmd(TIM4, ENABLE);  //使能TIM1   
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
		case 0://右轮
			TIM_SetCompare3(TIM4,sPWM);
			if (cSpeed>0) 
				RIGHT_MOTOR_GO_RESET;
			else if(cSpeed<0) 
				RIGHT_MOTOR_GO_SET;		
			break;
		case 1://左轮
		  TIM_SetCompare4(TIM4,sPWM); 
			if (cSpeed>0) 
				LEFT_MOTOR_GO_SET;
			else if (cSpeed<0)
				LEFT_MOTOR_GO_RESET;
			break;			
	}
}

//----------------------------------运动函数--------------------------------
void ZYSTM32_run(signed char speed,int time)  //前进函数
{
		  signed char f_speed = - speed;
	    SetMotorSpeed(1,f_speed);//左轮  //为负数
			SetMotorSpeed(0,speed);//右轮   //为正数
			delay_ms(time);                 //时间为毫秒

}

void ZYSTM32_brake(int time) //刹车函数
{
	  SetMotorSpeed(1,0);//左轮   //为0
	  SetMotorSpeed(0,0);//右轮   //为0
	  RIGHT_MOTOR_GO_RESET;
	  LEFT_MOTOR_GO_RESET;
		delay_ms(time);             //时间为毫秒  
}

void ZYSTM32_Left(signed char speed,int time) //左转函数
{
	  SetMotorSpeed(1,0);//左轮     //左轮不动
	  SetMotorSpeed(0,speed);        //右轮为正
		delay_ms(time);                 //时间为毫秒  

}
void ZYSTM32_Spin_Left(signed char speed,int time) //左旋转函数
{
	  SetMotorSpeed(1,speed);//左轮     //左轮为正
	  SetMotorSpeed(0,speed);            //右轮为正
		delay_ms(time);                    //时间为毫秒  

}
void ZYSTM32_Right(signed char speed,int time)  //右转函数
{
	  signed char f_speed = - speed;
	  SetMotorSpeed(1,f_speed);//左轮     //左轮为负
	  SetMotorSpeed(0,0);                 //右轮为0
		delay_ms(time);                   //时间为毫秒  

}
void ZYSTM32_Spin_Right(signed char speed,int time) //右旋转函数
{
	  signed char f_speed = - speed;
	  SetMotorSpeed(1,f_speed);//左轮     //左轮为负
	  SetMotorSpeed(0,f_speed);            //右轮为负
		delay_ms(time);                    //时间为毫秒  

}
void ZYSTM32_back(signed char speed,int time) //后退函数
{
	  signed char f_speed = - speed;
	  SetMotorSpeed(1,speed);//左轮   //为正数
	  SetMotorSpeed(0,f_speed);//右轮 //为负数
		delay_ms(time);                 //时间为毫秒  

}
