#include "keysacn.h"
#include "delay.h"
#include "stm32f10x.h"                  // Device header
//按键初始化函数 
//PA15和PC5 设置成输入
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//使能PORTA,PORTC时钟     
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;//PC2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC2
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				 //蜂鸣器PC3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//IO口速度为50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC.3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				       //LED0-->PA.8 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  //IO口速度为50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA.8
  GPIO_SetBits(GPIOA,GPIO_Pin_8);						            //PA.8 输出高

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	    		 //LED1-->PD.2 端口配置, 推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
  GPIO_SetBits(GPIOA,GPIO_Pin_4); 						       //PD.2 输出高 	  
	 
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PD.2 端口配置, 推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
  GPIO_SetBits(GPIOA,GPIO_Pin_5); 						       //PD.2 输出高 	
	 
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	    		 //LED1-->PD.2 端口配置, 推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
  GPIO_SetBits(GPIOA,GPIO_Pin_6); 						       //PD.2 输出高 	
}

void keysacn()
{
	u16 dtime = 34464;
  int val;
  val=KEY;  //读取按键
	delay_init();
  while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))//当按键没有被按下时，一直循环
  {
    val=KEY;//词句可省略，可让循环跑空
  }
  while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))//当按键被按下时
  {
    delay_ms(10);	  //延时10ms
    val=KEY;//读取数字端口PC2口电平值赋给Val
    if(val==1)  //第二次判断按键是否被按下
    {
    GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		GPIO_ResetBits(GPIOA,GPIO_Pin_6);
	  GPIO_SetBits(GPIOA,GPIO_Pin_4);
	  delay_ms(dtime);
	  GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		GPIO_ResetBits(GPIOA,GPIO_Pin_6);
	  GPIO_SetBits(GPIOA,GPIO_Pin_5);
		delay_ms(dtime);
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		GPIO_ResetBits(GPIOA,GPIO_Pin_6);
	  GPIO_SetBits(GPIOA,GPIO_Pin_6);
		delay_ms(dtime);
      while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))	//判断按时是否被松开
        BEEP_RESET;	//蜂鸣器停止
    }
    else
				BEEP_RESET;//蜂鸣器停止
  }
}
