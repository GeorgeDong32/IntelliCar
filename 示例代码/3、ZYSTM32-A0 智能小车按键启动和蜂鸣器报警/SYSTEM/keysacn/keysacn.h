#ifndef __KEYSACN_H_
#define __KEYSACN_H_

#include "stm32f10x.h"

void KEY_Init(void);//������ʼ��
void keysacn(void);//����ɨ�躯��

//������IO�ڶ���
#define BEEP_PIN         GPIO_Pin_3
#define BEEP_GPIO        GPIOC
#define BEEP_SET         GPIO_SetBits(BEEP_GPIO,BEEP_PIN)
#define BEEP_RESET       GPIO_ResetBits(BEEP_GPIO,BEEP_PIN)

//��ȡ����
#define KEY  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)//��ȡ����0

#endif
