#ifndef __USART_H
#define __USART_H

#include "board.h"
#include "fifo.h"

/**********************************************************
***	Emm_V5.0�����ջ���������
***	��д���ߣ�ZHANGDATOU
***	����֧�֣��Ŵ�ͷ�ջ��ŷ�
***	�Ա����̣�https://zhangdatou.taobao.com
***	CSDN���ͣ�http s://blog.csdn.net/zhangdatou666
***	qq����Ⱥ��262438510
**********************************************************/

extern __IO bool rxFrameFlag;
extern __IO uint8_t rxCmd[FIFO_SIZE];
extern __IO uint8_t rxCount;

extern __IO bool rxFrameFlag3;
extern __IO uint8_t rxCmd3[FIFO_SIZE];
extern __IO uint8_t rxCount3;

void usart_SendCmd(__IO uint8_t *cmd, uint8_t len);
void usart_SendByte(uint16_t data);
void usart_SendCmd3(__IO uint8_t *cmd, uint8_t len);
void usart_SendByte3(uint16_t data);

#endif
