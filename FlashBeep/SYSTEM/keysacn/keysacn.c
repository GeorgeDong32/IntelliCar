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
  // 初始化PC1为上拉输入
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  // 初始化PC3 Beep脚为推挽输出
  GPIO_InitStructure.GPIO_Pin = BEEP_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOC, BEEP_PIN);

  // 初始化PA5 LED红
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOA, GPIO_Pin_5);

  // 初始化PA8 LED黄
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOA, GPIO_Pin_8);

  // 初始化PA4 LED绿
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOA, GPIO_Pin_4);

  // 初始化PA6 LED蓝
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOA, GPIO_Pin_6);

  // 初始化PB6
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOB, GPIO_Pin_6);
}

void keysacn()
{
  // Define Zone
  u16 dtime = 500;
  int val;
  // End Define Zone
  KEY_Init();
  delay_init();

  val = KEY;
  GPIO_ResetBits(GPIOA, GPIO_Pin_5);
  GPIO_ResetBits(GPIOA, GPIO_Pin_4);
  GPIO_ResetBits(GPIOA, GPIO_Pin_6);
  BEEP_RESET;
  delay_init();
  if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1) || GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2))
  {
    delay_ms(500);
    if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2))
    {
      val = KEY;
      if (val == 1)
      {
        while (1)
        {
          GPIO_ResetBits(GPIOA, GPIO_Pin_4);
          GPIO_SetBits(GPIOA, GPIO_Pin_6);
          GPIO_ResetBits(GPIOA, GPIO_Pin_8);
          delay_ms(dtime);
          GPIO_SetBits(GPIOA, GPIO_Pin_4);
          GPIO_ResetBits(GPIOA, GPIO_Pin_6);
          GPIO_ResetBits(GPIOA, GPIO_Pin_8);
          delay_ms(dtime);
          GPIO_ResetBits(GPIOA, GPIO_Pin_4);
          GPIO_ResetBits(GPIOA, GPIO_Pin_6);
          GPIO_SetBits(GPIOA, GPIO_Pin_8);
          delay_ms(dtime);
          GPIO_ResetBits(GPIOA, GPIO_Pin_4);
          GPIO_ResetBits(GPIOA, GPIO_Pin_6);
          GPIO_ResetBits(GPIOA, GPIO_Pin_8);
          while (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2))
          {
            return;
          }
        }
      }
      else
      {
        return;
      }
    }
    if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1))
    {
      if (KEY1 == 1)
      {
        /*while (1)
        {
          BEEP_SET;
          delay_ms(25);
          BEEP_RESET;
          delay_ms(100);
          BEEP_SET;
          delay_ms(25);
          BEEP_RESET;
          delay_ms(3000);
          while (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1))
          {
            return;
          }
        }*/
        while (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1))
        {
          BEEP_SET;
          delay_ms(100);
        }
        while (!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1))
        {
          BEEP_RESET;
          return;
        }
      }
      else
      {
        return;
      }
    }
  }
  else
  {
    return;
  }
}

void indicator_flash(u16 dtime)
{
  GPIO_SetBits(GPIOA, GPIO_Pin_5);
  delay_ms(dtime);
  GPIO_ResetBits(GPIOA, GPIO_Pin_5);
}
