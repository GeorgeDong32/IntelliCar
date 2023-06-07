#include "IRSEARCH.h"
#include "delay.h"
#include "motor.h"
#include "stm32f10x.h"

char ctrl_comm = COMM_STOP;
char ctrl_comm_last = COMM_STOP;

void IRSearchInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = SEARCH_R_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SEARCH_R_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = SEARCH_L_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SEARCH_L_GPIO, &GPIO_InitStructure);
}

void SearchRun(void)
{
	if (SEARCH_L_IO == WHITE_AREA && SEARCH_R_IO == WHITE_AREA)
		ctrl_comm = COMM_UP;
	else if (SEARCH_L_IO == BLACK_AREA && SEARCH_R_IO == WHITE_AREA)
		ctrl_comm = COMM_LEFT;
	else if (SEARCH_R_IO == BLACK_AREA & SEARCH_L_IO == WHITE_AREA)
		ctrl_comm = COMM_RIGHT;
	else
		ctrl_comm = COMM_STOP;

	if (ctrl_comm_last != ctrl_comm)
	{
		ctrl_comm_last = ctrl_comm;
		switch (ctrl_comm)
		{
		case COMM_UP:
			Car_forward(50, 10);
			break;
		case COMM_DOWN:
			Car_back(50, 10);
			break;
		case COMM_LEFT:
			Car_left(50, 10);
			break;
		case COMM_RIGHT:
			Car_right(50, 10);
			break;
		case COMM_STOP:
			Car_brake(10);
			break;
		default:
			break;
		}
	}
}
