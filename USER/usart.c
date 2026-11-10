#include "usart.h"

__IO bool rxFrameFlag = false;
__IO uint8_t rxCmd[FIFO_SIZE] = {0};
__IO uint8_t rxCount = 0;

__IO bool rxFrameFlag3 = false;
__IO uint8_t rxCmd3[FIFO_SIZE] = {0};
__IO uint8_t rxCount3 = 0;

void USART2_IRQHandler(void)
{
	__IO uint16_t i = 0;

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		fifo_enQueue((uint8_t)USART2->DR);
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}

	else if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
	{
		USART2->SR; USART2->DR;
		rxCount = fifo_queueLength(); for(i=0; i < rxCount; i++) { rxCmd[i] = fifo_deQueue(); }
		rxFrameFlag = true;
	}
}

void USART3_IRQHandler(void)
{
	__IO uint16_t i = 0;

	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		fifo_enQueue3((uint8_t)USART3->DR);
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
	}

	else if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)
	{
		USART3->SR; USART3->DR;
		rxCount3 = fifo_queueLength3(); for(i=0; i < rxCount3; i++) { rxCmd3[i] = fifo_deQueue3(); }
		rxFrameFlag3 = true;
	}
}

void usart_SendCmd(__IO uint8_t *cmd, uint8_t len)
{
	__IO uint8_t i = 0;
	__IO uint16_t t0 = 0;
	
	for(i=0; i < len; i++) { usart_SendByte(cmd[i]); }
	
	while(!(USART2->SR & USART_FLAG_TC))
	{
		++t0; if(t0 > 8000) { return; }
	}
}

void usart_SendByte(uint16_t data)
{
	__IO uint16_t t0 = 0;
	
	USART2->DR = (data & (uint16_t)0x01FF);

	while(!(USART2->SR & USART_FLAG_TXE))
	{
		++t0; if(t0 > 8000)	{	return; }
	}
}

void usart_SendCmd3(__IO uint8_t *cmd, uint8_t len)
{
	__IO uint8_t i = 0;
	__IO uint16_t t0 = 0;
	
	for(i=0; i < len; i++) { usart_SendByte3(cmd[i]); }
	
	while(!(USART3->SR & USART_FLAG_TC))
	{
		++t0; if(t0 > 8000) { return; }
	}
}

void usart_SendByte3(uint16_t data)
{
	__IO uint16_t t0 = 0;
	
	USART3->DR = (data & (uint16_t)0x01FF);

	while(!(USART3->SR & USART_FLAG_TXE))
	{
		++t0; if(t0 > 8000)	{	return; }
	}
}
