#ifndef __KEYSACN_H_
#define __KEYSACN_H_

#include "stm32f10x.h"

void KEY_Init(void);//按键初始化
void keysacn(void);//按键扫描函数

//蜂鸣器IO口定义
#define BEEP_PIN         GPIO_Pin_3
#define BEEP_GPIO        GPIOC
#define BEEP_SET         GPIO_SetBits(BEEP_GPIO,BEEP_PIN)
#define BEEP_RESET       GPIO_ResetBits(BEEP_GPIO,BEEP_PIN)

// LED D3灯IO口定义
#define LED_D3_PIN       GPIO_Pin_6
#define LED_D3_PIN_GPIO  GPIOB
#define LED_D3_SET       GPIO_SetBits(LED_D3_PIN_GPIO,LED_D3_PIN)
#define LED_D3_RESET     GPIO_ResetBits(LED_D3_PIN_GPIO,LED_D3_PIN)

// LED D4灯IO口定义
#define LED_D4_PIN       GPIO_Pin_6
#define LED_D4_PIN_GPIO  GPIOA
#define LED_D4_SET       GPIO_SetBits(LED_D4_PIN_GPIO,LED_D4_PIN)
#define LED_D4_RESET     GPIO_ResetBits(LED_D4_PIN_GPIO,LED_D4_PIN)


//读取按键
#define KEY  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)//读取按键0

#endif
