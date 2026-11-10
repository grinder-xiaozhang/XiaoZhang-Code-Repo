#ifndef __UART_MAIXCAM_H
#define __UART_MAIXCAM_H

// 标准库所需头文件
#include "stm32f4xx.h"
#include <stdlib.h>

// 单轴数据最大缓存长度
#define RV_MAX_LEN 10

// 外部全局变量声明
extern volatile uint8_t rv_data_ready;
extern int16_t target_x;
extern int16_t target_y;
extern int16_t target_z;

// 函数声明
void Uart5_en_Init(void);// UART5串口初始化（标准库）
void Uart5_ProcessData(void);// 解析串口接收的三轴数据
int16_t Uart5_getdata(uint8_t choosexy);// 获取对应轴目标数据

#endif

