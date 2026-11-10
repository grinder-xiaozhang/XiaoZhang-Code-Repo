#include "pluse.h"


//根据脉冲计算走过的距离
float Count_Distance(long pulse)
{
    //脉冲除以一圈的脉冲乘以轮子的周长
	return ((pulse/LOOP_PULSE)*(WHEEL*3.1416));
}

//根据走过的距离计算要多少脉冲
float Count_Pulse(float distance)
{
    //根据距离算出要多少脉冲
	return (distance/(WHEEL*3.1416))*LOOP_PULSE;
}

//根据单脉冲计算一分钟能转多少圈
float Count_minute_turn(int pulse)
{
    //根据单次测到的脉冲计算一分钟多少脉冲
	float mid,result;
	mid=(pulse/PID_COMPUTATION_PERIOD)*1000.0;
	result=(mid*60)/LOOP_PULSE;
	return result;
}


