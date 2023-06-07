#include "keysacn.h"
#include "delay.h"
#include "stm32f10x.h"                  // Device header
//按键初始化函数 
//PA15和PC5 设置成输入
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);//使能PORTA,PORTC时钟     
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;//PC2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC2
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				 //蜂鸣器PC3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//IO口速度为50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC.3
	
	GPIO_InitStructure.GPIO_Pin = LED_D3_PIN;				 //LED D3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//IO口速度为50MHz
  GPIO_Init(LED_D3_PIN_GPIO, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.3
	
	GPIO_InitStructure.GPIO_Pin = LED_D4_PIN;				 //LED D4
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//IO口速度为50MHz
  GPIO_Init(LED_D4_PIN_GPIO, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC.3
}

void keysacn()
{
  int val;
  val=KEY;  //读取按键
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
      BEEP_SET;		//蜂鸣器响
      while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))	//判断按时是否被松开
        BEEP_RESET;	//蜂鸣器停止
    }
    else
				BEEP_RESET;//蜂鸣器停止
  }
}
