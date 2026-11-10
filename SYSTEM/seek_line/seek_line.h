#ifndef __SEEK_LINE_H
#define __SEEK_LINE_H

#include "stm32f4xx.h"

#define right4 PDin(10)
#define right3 PDin(11)
#define right2 PDin(12)
#define right1 PDin(13)
#define left1 PDin(14)
#define left2 PDin(15)
#define left3 PCin(6)
#define left4 PCin(7)
#define hou1  PDin(9)
void Seek_Line_Init(void);
void task1(void);
void task2(void);
void fengming(void);
void fengming2(void);
void fengming3(void);
void fengming4(void);
void Dright(void);
void Dleft(void);
void DIYITI(void);
void DIERTI(void);
void KUAIDIYITI(void);
void KUAIDIYITI2(void);
#endif /*__BSP_USART_H*/
