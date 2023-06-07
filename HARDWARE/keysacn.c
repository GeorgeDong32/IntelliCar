#include "keysacn.h"
#include "delay.h"
#include "stm32f10x.h"                  // Device header
//������ʼ������ 
//PA15��PC5 ���ó�����
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTA,PORTCʱ��     
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;//PC2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC2
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				 //������PC3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC.3
	
	GPIO_InitStructure.GPIO_Pin = LED_D3_PIN;				 //LED D3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//IO���ٶ�Ϊ50MHz
  GPIO_Init(LED_D3_PIN_GPIO, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.3
	
	GPIO_InitStructure.GPIO_Pin = LED_D4_PIN;				 //LED D4
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//IO���ٶ�Ϊ50MHz
  GPIO_Init(LED_D4_PIN_GPIO, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC.3
}

void keysacn()
{
  int val;
  val=KEY;  //��ȡ����
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
      BEEP_SET;		//��������
      while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))	//�жϰ�ʱ�Ƿ��ɿ�
        BEEP_RESET;	//������ֹͣ
    }
    else
				BEEP_RESET;//������ֹͣ
  }
}
