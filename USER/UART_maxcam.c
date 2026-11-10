#include "stm32f4xx.h"
#include <stdlib.h>  // atoi
#include <string.h>
#include "UART_maxcam.h"
#define RV_MAX_LEN 10
uint8_t u5_byte; 
uint8_t rv_state = 0;

uint8_t rv_x_buf[RV_MAX_LEN];
uint8_t rv_y_buf[RV_MAX_LEN];
uint8_t rv_z_buf[RV_MAX_LEN];
uint8_t rv_x_cnt = 0;
uint8_t rv_y_cnt = 0;
uint8_t rv_z_cnt = 0;

volatile uint8_t rv_data_ready = 0;

int16_t target_x = 0;
int16_t target_y = 0;
int16_t target_z = 0;

void Uart5_en_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    // 1. 开启时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);

    // PC12 TX
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOC, &GPIO_InitStruct);

    // PD2 RX
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOD, &GPIO_InitStruct);

    // 复用映射 UART5
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);

    // 2. USART5 参数配置 115200 8N1
    USART_InitStruct.USART_BaudRate = 115200;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(UART5, &USART_InitStruct);

    // 3. 开启接收非空中断 RXNE
    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
    USART_Cmd(UART5, ENABLE);

    // 4. NVIC 中断优先级配置
    NVIC_InitStruct.NVIC_IRQChannel = UART5_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}
void UART5_IRQHandler(void)
{
    if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
    {
        u5_byte = USART_ReceiveData(UART5);

        switch (u5_byte)
        {
            case 'X':
                rv_state = 1;
                rv_x_cnt = 0;
                break;

            case 'Y':
                rv_state = 2;
                rv_y_cnt = 0; 
                rv_x_buf[rv_x_cnt] = '\0';
                break;

            case 'Z':
                rv_state = 3;
                rv_z_cnt = 0; 
                rv_z_buf[rv_z_cnt] = '\0';
                break;

            case 'E': 
                rv_state = 0;
                rv_y_buf[rv_y_cnt] = '\0';
                rv_data_ready = 1;
                break;

            default:
                if (rv_state == 1) {
                    if (rv_x_cnt < RV_MAX_LEN - 1) {
                        rv_x_buf[rv_x_cnt++] = u5_byte;
                    }
                }
                else if (rv_state == 2) {
                    if (rv_y_cnt < RV_MAX_LEN - 1) {
                        rv_y_buf[rv_y_cnt++] = u5_byte;
                    }
                }
                else if (rv_state == 3) {
                    if (rv_z_cnt < RV_MAX_LEN - 1) {
                        rv_z_buf[rv_z_cnt++] = u5_byte;
                    }
                }
                break;
        }
    }
}

// 主循环轮询调用
void Uart5_ProcessData(void)
{
    if (rv_data_ready == 1)
    {
        target_x = atoi((char*)rv_x_buf);
        target_y = atoi((char*)rv_y_buf);
        target_z = atoi((char*)rv_z_buf);
        rv_data_ready = 0;
    }
}

// 获取三轴目标数据接口
int16_t Uart5_getdata(uint8_t choosexy)
{
    if(choosexy == 0)
        return target_z;
    else if (choosexy == 1)
        return target_x;
    else
        return target_y;
}
