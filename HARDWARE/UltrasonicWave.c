/******************** (C) 1209 Lab **************************
 * �ļ���  : UltrasonicWave.c
 * ����    �����������ģ�飬UltrasonicWave_Configuration��������
             ��ʼ������ģ�飬UltrasonicWave_StartMeasure��������
			 ������࣬������õ�����ͨ������1��ӡ����         
 * ʵ��ƽ̨��Mini STM32������  STM32F103RBT6
 * Ӳ�����ӣ�------------------
 *          | PC0  - TRIG      |
 *          | PC1  - ECHO      |
 *           ------------------
 * ��汾  ��ST3.5.0
 *
 * ����    ��Lee 
*********************************************************************************/

#include "UltrasonicWave.h"
#include "usart.h"
#include "timer.h"
#include "delay.h"


#define	TRIG_PORT      GPIOC		//TRIG       
#define	ECHO_PORT      GPIOC		//ECHO 
#define	TRIG_PIN       GPIO_Pin_0   //TRIG       
#define	ECHO_PIN       GPIO_Pin_1	//ECHO   

float UltrasonicWave_Distance;      //������ľ���    

/*
 * ��������UltrasonicWave_Configuration
 * ����  ��������ģ��ĳ�ʼ��
 * ����  ����
 * ���  ����	
 */
void UltrasonicWave_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
    
  GPIO_InitStructure.GPIO_Pin = TRIG_PIN;					  //PC0��TRIG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //��Ϊ�������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(TRIG_PORT, &GPIO_InitStructure);	      //��ʼ������GPIO 

  GPIO_InitStructure.GPIO_Pin = ECHO_PIN;				   //PC7��ECH0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		 //��Ϊ����
  GPIO_Init(ECHO_PORT,&GPIO_InitStructure);				 //��ʼ��GPIOA
	
	//GPIOC.1	  �ж����Լ��жϳ�ʼ������
 	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource1);

 	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);		                         //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
		
			
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			     //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	 //��ռ���ȼ�2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			   //�����ȼ�2 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;						 //ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);  	                         //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}

//------------------------ͨ��1�жϺ���---------------------------------------------
void EXTI1_IRQHandler(void)
{
	delay_us(10);		                      //��ʱ10us
  if(EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
			TIM_SetCounter(TIM2,0);
			TIM_Cmd(TIM2, ENABLE);                                       //����ʱ��
		
			while(GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN));	           //�ȴ��͵�ƽ

			TIM_Cmd(TIM2, DISABLE);			                                 //��ʱ��2ʧ��
			UltrasonicWave_Distance=TIM_GetCounter(TIM2)*5*34/200.0;			//�������&&UltrasonicWave_Distance<150
	  
//		   U_temp = 	UltrasonicWave_Distance*10;
//		if(UltrasonicWave_Distance>0)
//			{
//				printf("distance:%f mm",UltrasonicWave_Distance*10);
//			}
			EXTI_ClearITPendingBit(EXTI_Line1);  //���EXTI1��·����λ
	}
}
/*
 * ��������UltrasonicWave_StartMeasure
 * ����  ����ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
 * ����  ����
 * ���  ����	
 */
int UltrasonicWave_StartMeasure(void)
{
  int u_temp;
	GPIO_SetBits(TRIG_PORT,TRIG_PIN); 		  //��>10US�ĸߵ�ƽ�TRIG_PORT,TRIG_PIN��������define����?
  delay_us(20);		                      //��ʱ20US
  GPIO_ResetBits(TRIG_PORT,TRIG_PIN);
	u_temp = UltrasonicWave_Distance*10;
	return u_temp;
}

/******************* (C) 1209 Lab *****END OF FILE************/
