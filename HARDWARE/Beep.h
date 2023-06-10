#ifndef __BEEP_H__
#define __BEEP_H__

#include "stm32f10x.h"

#define BEEP_PIN GPIO_Pin_3
#define BEEP_GPIO GPIOC
#define BEEP_SET GPIO_SetBits(BEEP_GPIO, BEEP_PIN)
#define BEEP_RESET GPIO_ResetBits(BEEP_GPIO, BEEP_PIN)

void Beep_Init(void);

#endif
