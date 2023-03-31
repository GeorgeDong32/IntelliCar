#include "keysacn.h"
#include "delay.h"
#include "stm32f10x.h"                  // Device header
//������ʼ������ 
//PA15��PC5 ���ó�����
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTA,PORTCʱ��     
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;//PC2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC2
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				 //������PC3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC.3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				       //LED0-->PA.8 �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOA.8
  GPIO_SetBits(GPIOA,GPIO_Pin_8);						            //PA.8 �����

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	    		 //LED1-->PD.2 �˿�����, �������
  GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
  GPIO_SetBits(GPIOA,GPIO_Pin_4); 						       //PD.2 ����� 	  
	 
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PD.2 �˿�����, �������
  GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
  GPIO_SetBits(GPIOA,GPIO_Pin_5); 						       //PD.2 ����� 	
	 
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	    		 //LED1-->PD.2 �˿�����, �������
  GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
  GPIO_SetBits(GPIOA,GPIO_Pin_6); 						       //PD.2 ����� 	
}

void keysacn()
{
	u16 dtime = 34464;
  int val;
  val=KEY;  //��ȡ����
	delay_init();
  while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))//������û�б�����ʱ��һֱѭ��
  {
    val=KEY;//�ʾ��ʡ�ԣ�����ѭ���ܿ�
  }
  while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))//������������ʱ
  {
    delay_ms(10);	  //��ʱ10ms
    val=KEY;//��ȡ���ֶ˿�PC2�ڵ�ƽֵ����Val
    if(val==1)  //�ڶ����жϰ����Ƿ񱻰���
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
      while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))	//�жϰ�ʱ�Ƿ��ɿ�
        BEEP_RESET;	//������ֹͣ
    }
    else
				BEEP_RESET;//������ֹͣ
  }
}
