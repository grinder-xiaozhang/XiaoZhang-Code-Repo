#include "stm32f4xx.h"                   // Device header
#include "increpid.h"
#include "Encoder.h"
#include "OLED.h"  
#include <stdio.h>
#include <stdlib.h>
#include "Moter.h"
#include "math.h"
#include "Emm_V5.h"
You_PID Right_pid = {0, 0, 0, 0, 0, 0, 0};
Zuo_PID Left_pid = {0, 0, 0, 0, 0, 0, 0};
extern volatile int Left_Speed, Right_Speed;


float kp = 1;
float ki = 0.01;
float kd = 0.02;

float kp1 = 1;
float ki1 = 0.01;
float kd1 = 0.02; 

/*
Lspeed   左目标速度
Rspeed   右目-标速度
lastlastError   上上次误差
LastError   上次误差
Error    误差
result   结果
*/
void increment_PID(float Lspeed, float Rspeed)
{
	Left_pid._Error1 = (Lspeed - Left_Speed);
	Left_pid._p1 = (Left_pid._Error1 - Left_pid._LastError1);
	Left_pid._i1 = Left_pid._Error1;
	Left_pid._d1 = Left_pid._Error1 - 2 * Left_pid._LastError1 + Left_pid.lastlastError1;
	Left_pid.result1 += Left_pid._p1 * kp + Left_pid._i1 * ki + Left_pid._d1 * kd;
	Left_pid.lastlastError1 = Left_pid._LastError1;
	Left_pid._LastError1 = Left_pid._Error1;
	if(Left_pid.result1>320) Left_pid.result1=320;
	if(Left_pid.result1<-320) Left_pid.result1=-320;
	
	Right_pid._Error2 = (Rspeed - Right_Speed);
	Right_pid._p2 = (Right_pid._Error2 - Right_pid._LastError2);
	Right_pid._i2 = Right_pid._Error2;
	Right_pid._d2 = Right_pid._Error2 - 2 * Right_pid._LastError2 + Right_pid.lastlastError2; // 等于这次误差减去两倍上次误差加上上上次误差
	Right_pid.result2 += Right_pid._p2 * kp1 + Right_pid._i2 * ki1 + Right_pid._d2 * kd1;
	Right_pid.lastlastError2 = Right_pid._LastError2;
	Right_pid._LastError2 = Right_pid._Error2;
	if(Right_pid.result2>320) Right_pid.result2=320;
	if(Right_pid.result2<-320) Right_pid.result2=-320;

	Motor_speed(Left_pid.result1, Right_pid.result2);
}

extern int Yaw;


//#define angle_p 0.495f
//#define angle_d 0.02f  

#define angle_p 1.8f	 //1.8f		2.0f	
#define angle_i 0.01f  //0.01f  0.15f
#define angle_d 0.07f  //0.07f  0.15f



float angleError;
float angleLastError;
long angle_bias;


void angle_PID(float Lspeed, float Rspeed, int angle)
{
    angleError = angle - Yaw;  // 目标角度减去现在的角度
    
    angle_bias+=angleError;
	if(angle_bias>45.0)
	{
		angle_bias=45;
	}
	else if(angle_bias<-45.0)
	{
		angle_bias=-45;
	}
	/*陀螺仪只能到 179 -179 如果想转180度 误差只有两种 1 356   正常来说误差是不会大于180的*/
	if(angleError>180)
	{
		angleError=angleError-360;
	}
	if(angleError<-180)
	{
		angleError=angleError+360;
	}
	
	float result = angleError * angle_p + angle_bias*angle_i+angle_d *(angleError-angleLastError);
	angleLastError=angleError;

	increment_PID(Lspeed-result,Rspeed+result);

}




