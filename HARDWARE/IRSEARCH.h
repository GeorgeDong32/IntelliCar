#ifndef __IRSEARCH_H_
#define __IRSEARCH_H_

#include "stm32f10x.h"

void IRSearchInit(void);
void SearchRun(void);

//循迹光电对管
/* 
右循迹	SEARCH_R_PIN	PA7
左循迹	SEARCH_L_PIN	PB0
 */

#define SEARCH_R_PIN         GPIO_Pin_7
#define SEARCH_R_GPIO        GPIOA
#define SEARCH_R_IO          GPIO_ReadInputDataBit(SEARCH_R_GPIO, SEARCH_R_PIN)

#define SEARCH_L_PIN         GPIO_Pin_0
#define SEARCH_L_GPIO        GPIOB
#define SEARCH_L_IO          GPIO_ReadInputDataBit(SEARCH_L_GPIO, SEARCH_L_PIN)
#define BLACK_AREA 1
#define WHITE_AREA 0


//指令定义
#define COMM_STOP  'I'//停止
#define COMM_UP    'A'//前进
#define COMM_DOWN  'B'//后退
#define COMM_LEFT  'C'//左转
#define COMM_RIGHT 'D'//右转



#endif
