#ifndef _TOF050F_H
#define _TOF050F_H
#include "stm32f4xx.h"

typedef unsigned char bool;
#define true 1
#define false 0

void TOF050F_Iint(u32 bound);
void usart_SendCmd4(__IO uint8_t *cmd, uint8_t len);
void usart_SendByte4(uint16_t data);
void Emm_V5_Vel_Control4(uint8_t addr, uint8_t dir, uint16_t vel, uint8_t acc, bool snF);
void Emm_V5_Pos_Control4(uint8_t addr, uint8_t dir, uint16_t vel, uint8_t acc, uint32_t clk, bool raF, bool snF);

#endif
