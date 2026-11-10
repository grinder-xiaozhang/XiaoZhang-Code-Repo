#ifndef __FIFO_H
#define __FIFO_H

#include "stm32f4xx.h"

typedef unsigned char bool;
#define true 1
#define false 0

#define 	FIFO_SIZE   128
typedef struct {
	uint16_t buffer[FIFO_SIZE];
	__IO uint8_t ptrWrite;
	__IO uint8_t ptrRead;
}FIFO_t;

extern __IO FIFO_t rxFIFO;
extern __IO FIFO_t rxFIFO3;

void fifo_initQueue(void);
void fifo_initQueue3(void);
void fifo_enQueue(uint16_t data);
void fifo_enQueue3(uint16_t data);
uint16_t fifo_deQueue(void);
uint16_t fifo_deQueue3(void);
bool fifo_isEmpty(void);
bool fifo_isEmpty3(void);
bool fifo_isFull(void);
bool fifo_isFull3(void);
uint16_t fifo_queueLength(void);
uint16_t fifo_queueLength3(void);

#endif
