#ifndef __KEY_H
#define __KEY_H

#include "stm32f4xx.h"

#define LED0 PBout(13)
#define LED1 PBout(14)
#define BEEP PCout(2)
#define buzzer_ON() GPIO_ResetBits(GPIOC,GPIO_Pin_2);
#define buzzer_OFF() GPIO_SetBits(GPIOC,GPIO_Pin_2);
void Key_Init(void);
void LED_Init(void);
void EXTIXa_Init(void);

#endif /*__BSP_USART_H*/
