#ifndef __IRAVOID_H_
#define __IRAVOID_H_

#include "stm32f10x.h"

void IRAvoidInit(void);
void AVoidRun(void);

#define AVOID_PIN GPIO_Pin_1
#define AVOID_PIN_GPIO GPIOB
#define AVOID_IO GPIO_ReadInputDataBit(AVOID_PIN_GPIO, AVOID_PIN)
#define BARRIER_Y 0
#define BARRIER_N 1

#endif
