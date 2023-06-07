#ifndef __IRAVOID_H_
#define __IRAVOID_H_

#include "stm32f10x.h"                  // Device header

void IRAvoidInit(void);
void AVoidRun(void);

//避障传感器
/* 
避障传感器 AVOID_PIN	PB1
 */

#define AVOID_PIN         GPIO_Pin_1
#define AVOID_PIN_GPIO    GPIOB
#define AVOID_IO          GPIO_ReadInputDataBit(AVOID_PIN_GPIO, AVOID_PIN)
#define BARRIER_Y 0      //有障碍物
#define BARRIER_N 1      //无障碍物



#endif
