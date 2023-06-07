#include "keysacn.h"
#include "delay.h"
#include "stm32f10x.h"

void KEY_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = LED_D3_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LED_D3_PIN_GPIO, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = LED_D4_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LED_D4_PIN_GPIO, &GPIO_InitStructure);
}

void keysacn()
{
  int val;
  val = KEY;
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
      BEEP_SET;
      while (!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2))
        BEEP_RESET;
    }
    else
      BEEP_RESET;
  }
}
