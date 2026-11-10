#ifndef _INCREPID_H
#define _INCREPID_H
#include <stdio.h>
#include <stdlib.h>


typedef struct 
{
	float _p2;
	float _i2;
	float _d2;
	float _Error2;
	float _LastError2;
	float lastlastError2;
	float result2;
}You_PID;

typedef struct 
{
	float _p1;
	float _i1;
	float _d1;
	float _Error1;
	float _LastError1;
	float lastlastError1;
	float result1;
}Zuo_PID;

void increment_PID(float Lspeed, float Rspeed);
void angle_PID(float Lspeed, float Rspeed, int angle);
#endif
