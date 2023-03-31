#include "keysacn.h"
#include "delay.h"
#include "stm32f10x.h"

void KEY_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  // 初始化PC2为上拉输入
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  // 初始化PC3 Beep脚为推挽输出
  GPIO_InitStructure.GPIO_Pin = BEEP_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  // 初始化PA8为推挽输出
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA, GPIO_Pin_8);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA, GPIO_Pin_4);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; // LED1-->PD.2 �˿�����, �������
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA, GPIO_Pin_5); // PD.2 �����

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; // LED1-->PD.2 �˿�����, �������
  GPIO_Init(GPIOA, &GPIO_InitStructure);    // ������� ��IO���ٶ�Ϊ50MHz
  GPIO_SetBits(GPIOA, GPIO_Pin_6);          // PD.2 �����
}

void keysacn()
{
  u16 dtime = 1000;
  int val;
  val = KEY;
  delay_init();
  while (!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2))
  {
    val = KEY;
  }
  while (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2))
  {
    delay_ms(10);
    val = KEY;
    if (val == 1)
    {
      GPIO_ResetBits(GPIOA, GPIO_Pin_4);
      GPIO_ResetBits(GPIOA, GPIO_Pin_5);
      GPIO_ResetBits(GPIOA, GPIO_Pin_6);
      GPIO_SetBits(GPIOA, GPIO_Pin_4);
      delay_ms(dtime);
      GPIO_ResetBits(GPIOA, GPIO_Pin_4);
      GPIO_ResetBits(GPIOA, GPIO_Pin_5);
      GPIO_ResetBits(GPIOA, GPIO_Pin_6);
      GPIO_SetBits(GPIOA, GPIO_Pin_5);
      delay_ms(dtime);
      GPIO_ResetBits(GPIOA, GPIO_Pin_4);
      GPIO_ResetBits(GPIOA, GPIO_Pin_5);
      GPIO_ResetBits(GPIOA, GPIO_Pin_6);
      GPIO_SetBits(GPIOA, GPIO_Pin_6);
      delay_ms(dtime);
      while (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2))
        BEEP_SET;
    }
    else
      BEEP_RESET;
  }
}
