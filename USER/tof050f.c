#include "tof050f.h"
#include "sys.h"

__IO bool rxFrameFlag4 = false;
__IO uint8_t rxCmd4[128] = {0};
__IO uint8_t rxCount4 = 0;

void TOF050F_Iint(u32 bound)
{
     GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);

    GPIO_PinAFConfig(GPIOD,GPIO_PinSource0,GPIO_AF_UART4); 
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF_UART4); 
    
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
    GPIO_Init(GPIOD,&GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = bound;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    
		USART_Init(UART4, &USART_InitStructure);
    
		USART_Cmd(UART4, ENABLE);  

    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
    USART_ITConfig(UART4, USART_IT_IDLE, ENABLE);

		NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;        
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            
    NVIC_Init(&NVIC_InitStructure);    
}

void UART4_IRQHandler(void)
{
	__IO uint16_t i = 0;

	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(UART4, USART_IT_RXNE);
	}

	else if(USART_GetITStatus(UART4, USART_IT_IDLE) != RESET)
	{
		UART4->SR; UART4->DR;
		rxFrameFlag4 = true;
	}
}

void usart_SendCmd4(__IO uint8_t *cmd, uint8_t len)
{
	__IO uint8_t i = 0;
	__IO uint16_t t0 = 0;
	
	for(i=0; i < len; i++) { usart_SendByte4(cmd[i]); }
	
	while(!(UART4->SR & USART_FLAG_TC))
	{
		++t0; if(t0 > 8000) { return; }
	}
}

void usart_SendByte4(uint16_t data)
{
	__IO uint16_t t0 = 0;
	
	UART4->DR = (data & (uint16_t)0x01FF);

	while(!(UART4->SR & USART_FLAG_TXE))
	{
		++t0; if(t0 > 8000)	{	return; }
	}
}

void Emm_V5_Vel_Control4(uint8_t addr, uint8_t dir, uint16_t vel, uint8_t acc, bool snF)
{
  __IO static uint8_t cmd[16] = {0};

  cmd[0] =  addr;
  cmd[1] =  0xF6;
  cmd[2] =  dir;
  cmd[3] =  (uint8_t)(vel >> 8);
  cmd[4] =  (uint8_t)(vel >> 0);
  cmd[5] =  acc;
  cmd[6] =  snF;
  cmd[7] =  0x6B;
  
  usart_SendCmd4(cmd, 8);
}

void Emm_V5_Pos_Control4(uint8_t addr, uint8_t dir, uint16_t vel, uint8_t acc, uint32_t clk, bool raF, bool snF)
{
  __IO static uint8_t cmd[16] = {0};

  cmd[0]  =  addr;
  cmd[1]  =  0xFD;
  cmd[2]  =  dir;
  cmd[3]  =  (uint8_t)(vel >> 8);
  cmd[4]  =  (uint8_t)(vel >> 0);
  cmd[5]  =  acc;
  cmd[6]  =  (uint8_t)(clk >> 24);
  cmd[7]  =  (uint8_t)(clk >> 16);
  cmd[8]  =  (uint8_t)(clk >> 8);
  cmd[9]  =  (uint8_t)(clk >> 0);
  cmd[10] =  raF;
  cmd[11] =  snF;
  cmd[12] =  0x6B;
  
  usart_SendCmd4(cmd, 13);
}
