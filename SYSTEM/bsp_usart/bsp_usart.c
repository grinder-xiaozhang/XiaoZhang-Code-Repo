#include "bsp_usart.h"
#include <stdio.h>
#include <stdarg.h>
#include "stm32f4xx.h"


void uart1_init(void)
{
	// ����һ��GPIO��ʼ���ṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	// ����һ��USART��ʼ���ṹ��
	USART_InitTypeDef USART_InitStructure;
	// ����һ��NVIC��ʼ���ṹ��
	NVIC_InitTypeDef NVIC_InitStructure;

	// ʹ��GPIOAʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	// ʹ��UART1ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	// ----------------- UART1 �˿����� -----------------
	// ��GPIOA��Pin9����ΪUSART1�����蹦��
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	// ��GPIOA��Pin10����ΪUSART1�����蹦��
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	// ����GPIO_PinΪ9��10����PA9TX��PA10RX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	// ����GPIOģʽΪ���ù���ģʽ������USART
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	// ����GPIO����ٶ�Ϊ50MHz
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	// ����GPIO�������Ϊ�������
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	// ����GPIO����/����Ϊ����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	// ��ʼ��GPIOA
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// ----------------- UART1 ��ʼ������ -----------------

	// ���ò�����Ϊ115200
	USART_InitStructure.USART_BaudRate = 115200;
	// �������ݸ�ʽΪ8λ���ݳ���
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����һ��ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ��ʹ����żУ��λ
	USART_InitStructure.USART_Parity = USART_Parity_No;
	// ��ʹ��Ӳ������������
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// ����USARTΪ�շ�ģʽ
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ʼ��UART1
	USART_Init(USART1, &USART_InitStructure);

	// ����UART1�����ж�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);

	// ----------------- UART1 NVIC ���� -----------------

	// ����NVIC�ж�ͨ��ΪUART1�ж�
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	// ������ռ���ȼ�Ϊ3
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	// ���������ȼ�Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	// ʹ�ܸ��ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// ��ʼ��NVIC
	NVIC_Init(&NVIC_InitStructure);

	// ʹ��UART1
	USART_Cmd(USART1, ENABLE);
}

void uart2_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(USART2, ENABLE);
}

void uart3_init(void)
{
	// ����һ��GPIO��ʼ���ṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	// ����һ��USART��ʼ���ṹ��
	USART_InitTypeDef USART_InitStructure;
	// ����һ��NVIC��ʼ���ṹ��
	NVIC_InitTypeDef NVIC_InitStructure;

	// ʹ��GPIOBʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	// ʹ��UART3ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	// ----------------- UART3 �˿����� -----------------
	// ��GPIOB��Pin10����ΪUSART3�����蹦��
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
	// ��GPIOB��Pin11����ΪUSART3�����蹦��
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);
	// ����GPIO_PinΪ10��11����PB10TX��PB11RX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	// ����GPIOģʽΪ���ù���ģʽ������USART
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	// ����GPIO����ٶ�Ϊ50MHz
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	// ����GPIO�������Ϊ�������
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	// ����GPIO����/����Ϊ����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	// ��ʼ��GPIOB
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// ----------------- UART1 ��ʼ������ -----------------

	// ���ò�����Ϊ115200
	USART_InitStructure.USART_BaudRate = 115200;
	// �������ݸ�ʽΪ8λ���ݳ���
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����һ��ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ��ʹ����żУ��λ
	USART_InitStructure.USART_Parity = USART_Parity_No;
	// ��ʹ��Ӳ������������
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// ����USARTΪ�շ�ģʽ
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ʼ��UART3
	USART_Init(USART3, &USART_InitStructure);

	// ����UART3�����ж�
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);

	// ----------------- UART1 NVIC ���� -----------------

	// ����NVIC�ж�ͨ��ΪUART3�ж�
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	// ������ռ���ȼ�Ϊ3
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	// ���������ȼ�Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	// ʹ�ܸ��ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// ��ʼ��NVIC
	NVIC_Init(&NVIC_InitStructure);

	// ʹ��UART3
	USART_Cmd(USART3, ENABLE);
}

/**
  * ��    �������ڷ���һ���ֽ�
  * ��    ����Byte Ҫ���͵�һ���ֽ�
  * �� �� ֵ����
  */
void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1, Byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void Serial3_SendByte(uint8_t Byte)
{
	USART_SendData(USART3, Byte);
	while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
}


void setJy92_Yaw_Zero(void)
{
    Serial_SendByte(0xff);
    Serial_SendByte(0xaa);
    Serial_SendByte(0x52);
}
