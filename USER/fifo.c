#include "fifo.h"

__IO FIFO_t rxFIFO = {0};
__IO FIFO_t rxFIFO3 = {0};

void fifo_initQueue(void)
{
	rxFIFO.ptrRead  = 0;
	rxFIFO.ptrWrite = 0;
}

void fifo_initQueue3(void)
{
	rxFIFO3.ptrRead  = 0;
	rxFIFO3.ptrWrite = 0;
}

void fifo_enQueue(uint16_t data)
{
	if(fifo_isFull())
	{
		return;
	}
	
	rxFIFO.buffer[rxFIFO.ptrWrite] = data;
	
	++rxFIFO.ptrWrite;
	
	if(rxFIFO.ptrWrite >= FIFO_SIZE)
	{
		rxFIFO.ptrWrite = 0;
	}
}

void fifo_enQueue3(uint16_t data)
{
	if(fifo_isFull3())
	{
		return;
	}
	
	rxFIFO3.buffer[rxFIFO3.ptrWrite] = data;
	
	++rxFIFO3.ptrWrite;
	
	if(rxFIFO3.ptrWrite >= FIFO_SIZE)
	{
		rxFIFO3.ptrWrite = 0;
	}
}

uint16_t fifo_deQueue(void)
{
	if(fifo_isEmpty())
	{
		return 0;
	}
	
	uint16_t element = rxFIFO.buffer[rxFIFO.ptrRead];

	++rxFIFO.ptrRead;

	if(rxFIFO.ptrRead >= FIFO_SIZE)
	{
		rxFIFO.ptrRead = 0;
	}

	return element;
}

uint16_t fifo_deQueue3(void)
{
	if(fifo_isEmpty3())
	{
		return 0;
	}
	
	uint16_t element = rxFIFO3.buffer[rxFIFO3.ptrRead];

	++rxFIFO3.ptrRead;

	if(rxFIFO3.ptrRead >= FIFO_SIZE)
	{
		rxFIFO3.ptrRead = 0;
	}

	return element;
}

bool fifo_isEmpty(void)
{
	if(rxFIFO.ptrRead == rxFIFO.ptrWrite)
	{
		return true;
	}

	return false;
}

bool fifo_isEmpty3(void)
{
	if(rxFIFO3.ptrRead == rxFIFO3.ptrWrite)
	{
		return true;
	}

	return false;
}

bool fifo_isFull(void)
{
	uint8_t nextWrite = rxFIFO.ptrWrite + 1;
	if(nextWrite >= FIFO_SIZE)
	{
		nextWrite = 0;
	}
	
	return (nextWrite == rxFIFO.ptrRead);
}

bool fifo_isFull3(void)
{
	uint8_t nextWrite = rxFIFO3.ptrWrite + 1;
	if(nextWrite >= FIFO_SIZE)
	{
		nextWrite = 0;
	}
	
	return (nextWrite == rxFIFO3.ptrRead);
}

uint16_t fifo_queueLength(void)
{
	if(rxFIFO.ptrRead <= rxFIFO.ptrWrite)
	{
		return (rxFIFO.ptrWrite - rxFIFO.ptrRead);
	}
	else
	{
		return (FIFO_SIZE - rxFIFO.ptrRead + rxFIFO.ptrWrite);
	}
}

uint16_t fifo_queueLength3(void)
{
	if(rxFIFO3.ptrRead <= rxFIFO3.ptrWrite)
	{
		return (rxFIFO3.ptrWrite - rxFIFO3.ptrRead);
	}
	else
	{
		return (FIFO_SIZE - rxFIFO3.ptrRead + rxFIFO3.ptrWrite);
	}
}
