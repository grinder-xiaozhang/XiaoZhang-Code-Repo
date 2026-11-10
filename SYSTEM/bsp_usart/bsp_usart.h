#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "stm32f4xx.h"

void uart1_init(void);
void uart2_init(void);
void uart3_init(void);
void Serial_SendByte(uint8_t Byte);
void Serial3_SendByte(uint8_t Byte);
void setJy92_Yaw_Zero(void);

#endif /*__BSP_USART_H*/
