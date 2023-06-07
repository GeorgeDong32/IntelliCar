#ifndef __IRSEARCH_H_
#define __IRSEARCH_H_

#include "stm32f10x.h"

void IRSearchInit(void);
void SearchRun(void);

#define SEARCH_R_PIN GPIO_Pin_7
#define SEARCH_R_GPIO GPIOA
#define SEARCH_R_IO GPIO_ReadInputDataBit(SEARCH_R_GPIO, SEARCH_R_PIN)

#define SEARCH_L_PIN GPIO_Pin_0
#define SEARCH_L_GPIO GPIOB
#define SEARCH_L_IO GPIO_ReadInputDataBit(SEARCH_L_GPIO, SEARCH_L_PIN)
#define BLACK_AREA 1
#define WHITE_AREA 0

#define COMM_STOP 'I'
#define COMM_UP 'A'
#define COMM_DOWN 'B'
#define COMM_LEFT 'C'
#define COMM_RIGHT 'D'

#endif
