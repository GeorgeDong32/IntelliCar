
#include "stm32f10x.h"
void Delay(u32 count)
{
	u32 i = 0;
	for (; i < count; i++)
	{
	}
}

int main(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	u32 FlashTime = 5000000;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD, ENABLE); // ʹ��PA,PD�˿�ʱ��

	// ��ʼ��PA5ʱ��ָʾ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;		  // LED0-->PA.8 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);			  // �����趨������ʼ��GPIOA.8
	GPIO_SetBits(GPIOA, GPIO_Pin_5);				  // PA.8 �����

	// ��ʼ��PA6����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_6);

	// ��ʼ��PA4�Ƶ�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);

	// ��ʼ��PA2���
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_2);

	// ��ʼ��PA3�̵�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_3);

	// ��ʼ��GND�ӵ���
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; // LED1-->PD.2 �˿�����, �������
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  // ������� ��IO���ٶ�Ϊ50MHz
	GPIO_SetBits(GPIOD, GPIO_Pin_2);		  // PD.2 �����
	while (1)
	{
		// Set���ƣ�Reset���
		// �̻ƺ���������˸

		// ��ʼ������
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		GPIO_ResetBits(GPIOA, GPIO_Pin_6);

		// ��˸����
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		GPIO_SetBits(GPIOA, GPIO_Pin_3);
		Delay(FlashTime);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		Delay(FlashTime);

		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
		Delay(FlashTime);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		Delay(FlashTime);

		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
		Delay(FlashTime);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		Delay(FlashTime);

		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		GPIO_SetBits(GPIOA, GPIO_Pin_6);
		Delay(FlashTime);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		Delay(FlashTime);
	}
}
