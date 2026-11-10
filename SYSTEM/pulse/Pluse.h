#ifndef _PLUSE_H
#define _PLUSE_H
#include "stm32f4xx.h"
//编码器测速几倍频
#define RESOLUTION  4
//电机是几线的电机  MG310 = 13线
#define RESOLUTION_TOTAL 13.0
//电机减速比        MG310 = 20
#define REDUCTION_RATIO 20.0
//电机转一圈产生多少脉冲
#define LOOP_PULSE (RESOLUTION*RESOLUTION_TOTAL*REDUCTION_RATIO)
//轮子的直径 cm
#define WHEEL 4.8f
//每隔多久测一次脉冲
#define PID_COMPUTATION_PERIOD  20.0

float Count_Distance(long pulse);//根据累计脉冲计算距离
float Count_Pulse(float distance);//根据走过的距离计算要多少脉冲
float Count_minute_turn(int pulse);//根据单脉冲计算一分钟能转多少圈




#endif

