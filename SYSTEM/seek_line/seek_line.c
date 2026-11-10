#include "stm32f4xx.h"
#include "seek_line.h"
#include "sys.h"

uint8_t left,right,flag,mode1,mode2,flag_z,flag111=0;
extern double distance;
extern double distance2;
extern double distance3;
extern int Left_Speed_cnt;
extern int Right_Speed_cnt;
extern uint8_t x;
extern uint16_t cnttt1,cnttt2;
extern int xmode1,ymode1,zmode1,amode1,cmode1;
extern int a,b,c,d,e,Yaw;
extern uint8_t number;
uint8_t distance_flag = 0,state;  // 添加标志位
//int xmode1=0;
//int a=0,b=0,c=0,d=0,e=0;
void Seek_Line_Init(void)
{
	// 定义一个GPIO初始化结构体
	GPIO_InitTypeDef GPIO_InitTypeDefstruct;
	// 使能GPIOD时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	// 设置GPIO模式为输入
	GPIO_InitTypeDefstruct.GPIO_Mode=GPIO_Mode_IN;

	// 设置GPIO引脚为10、11、12、13、14
	GPIO_InitTypeDefstruct.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_9;;
	// 设置GPIO上拉电阻
	GPIO_InitTypeDefstruct.GPIO_PuPd=GPIO_PuPd_UP;
	// 设置GPIO速度为50MHz
	GPIO_InitTypeDefstruct.GPIO_Speed=GPIO_Speed_50MHz;
	// 初始化GPIOD
	GPIO_Init(GPIOD,&GPIO_InitTypeDefstruct);
	GPIO_InitTypeDefstruct.GPIO_Pin=GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOC,&GPIO_InitTypeDefstruct);
}


////******近端********		//左右轮通用型		近端
void task1(void)
{	
	if(left1!=0)
	{
	increment_PID(80,80);
	}
	if(right1!=0)
	{
		increment_PID(80,80);
	}
	if(left2!=0)
	{
	increment_PID(50,95);
	}
	if(right2!=0)
	{
		increment_PID(95,50);
	}
	if(left3!=0)
	{
	increment_PID(40,125);
	}
	if(right3!=0)
	{
		increment_PID(125,40);
	}
	if(left4!=0)
	{
	increment_PID(20,145);
	}
	if(right4!=0)
	{
		increment_PID(145,20);
	}
	 if(left1==0&&right1==0&&right2==0&&left2==0&&left3==0&&right3==0&&right4==0&&left4==0)
	{
		increment_PID(80,80);
	}
}
void task2(void)
{	
	if(left1!=0)
	{
	increment_PID(40,40);
	}
	if(right1!=0)
	{
		increment_PID(40,40);
	}
	if(left2!=0)
	{
	increment_PID(25,46);
	}
	if(right2!=0)
	{
		increment_PID(46,25);
	}
	if(left3!=0)
	{
	increment_PID(20,62);
	}
	if(right3!=0)
	{
		increment_PID(62,20);
	}
	if(left4!=0)
	{
	increment_PID(15,70);
	}
	if(right4!=0)
	{
		increment_PID(70,15);
	}
	 if(left1==0&&right1==0&&right2==0&&left2==0&&left3==0&&right3==0&&right4==0&&left4==0)
	{
		increment_PID(40,40);
	}
}
//}	
//}
////******中端********					//中端
void Dleft(void)
{

	increment_PID(20,105);

}
void Dright(void)
{

	increment_PID(105,20);

}
		
void DIYITI(void)
{
	task1();
	if(left1+left2+left3+left4+right1>=3&&mode1==0)
	{
	
	mode1=1;
	
	}
	
	if(	mode1==1)
	{
		angle_PID(10,90,120);
		a++;
		if(a>=1300)
		{
		mode1=2;
			a=0;
			distance=0;
			Left_Speed_cnt=0;
			Right_Speed_cnt=0;
		}
	}
	if(	mode1==2)
	{
	task1();
	if( distance>=24&&(right1+right2+left1+left2==0))
		{
		a++;
			if(a>=500)
			{mode1=3;
					distance=0;
			Left_Speed_cnt=0;
			Right_Speed_cnt=0;
			a=0;
			}
		
		}
	}
	if(mode1==3)
	{
	
		angle_PID(30,90,-120);
		if((right1+right2+left1+left2+right3+right4+left3+left4>=1)&&	distance>=12)
		{
		a++;
			if(a>=600)
			{
			mode1=4;
						distance=0;
			Left_Speed_cnt=0;
			Right_Speed_cnt=0;
				a=0;
			}
		}
	}
	if(mode1==4)
	{
	task1();
		if(right1+right2+left1+left2==0&&distance>=6)
		{
		a++;
		if(a>=500)
		{
			mode1=5;
			a=0;
		
		}
		}
	}
	if(mode1==5)
	{
	
	angle_PID(90,90,-120);
		if(left3+left4+left2>=2)
	{
	
	mode1=6;
	}
	}


	if(mode1==6)
	{
	Motor_speed(0,0);
	
	}

}


void DIERTI(void)
{
task1();
	if(left1+left2+left3+left4+right1>=3&&mode1==0)
	{
	
	mode1=1;
	
	}
	
	if(	mode1==1)
	{
		angle_PID(10,90,120);
		a++;
		if(a>=1300)
		{
		mode1=2;
			a=0;
			distance=0;
			Left_Speed_cnt=0;
			Right_Speed_cnt=0;
		}
	}
	if(	mode1==2)
	{
	task1();
	if( distance>=28&&(right1+right2+left1+left2==0))
		{
		a++;
			if(a>=500)
			{mode1=3;
					distance=0;
			Left_Speed_cnt=0;
			Right_Speed_cnt=0;
			a=0;
			}
		
		}
	}
	if(mode1==3)
	{
	
		angle_PID(30,90,-120);
		if((right1+right2+left1+left2+right3+right4+left3+left4>=1)&&	distance>=12)
		{
		a++;
			if(a>=600)
			{
			mode1=4;
						distance=0;
			Left_Speed_cnt=0;
			Right_Speed_cnt=0;
				a=0;
			}
		}
	}
	if(mode1==4)
	{
	task1();
		if(right1+right2+left1+left2==0&&distance>=6)
		{
		a++;
		if(a>=500)
		{
			mode1=5;
			a=0;
		
		}
		}
	}
	if(mode1==5)
	{
	
	angle_PID(90,90,-120);
		if(left3+left4+left2>=2)
	{
	
	mode1=6;
	}
	}
	if(mode1==6&&mode2==0)
	{
angle_PID(10,90,0);
	a++;
		if(a>=1300)
		{
		mode1=7;
		distance=0;
		Left_Speed_cnt=0;
		Right_Speed_cnt=0;
			a=0;
		}
	}
if(mode1==7)
{
task1();
	if(distance>=12&&(left1+left2+left3+left4+right1>=3))
	{
	mode2=1;
	mode1=1;
	}

}
if(mode2==1&&mode1==6)
{

Motor_speed(0,0);

}

}





void KUAIDIYITI(void)
{ 
	if(mode1==0)
	{ 
		if(Yaw<=2&&Yaw>=-2)
	   {
			 angle_PID(130,130,0);
		 }
		 else
		 {
		 task1();
		 }
	}
	if(distance>=83&&mode1==0&&mode2==0)
	{
		mode1=1;
	}
	if(mode1==0&&mode2==1&&((left4+left2+left3>=2)))
	{
	
	mode1=1;
	
	}
	if(mode1==1)
	{  //	angle_PID(0,130,120);
			distance=0;
			Left_Speed_cnt=0;
			Right_Speed_cnt=0;
		  mode1=20;
	}
	if(mode1==20)
	{
		angle_PID(130,130,125);
		if(Yaw>=115)
		{
		mode1=2;
			
		}
	}

	if(mode1==2)
	{ 
		if(Yaw<=123&&Yaw>=117)
		{
		angle_PID(130,130,120);
		}
		else
		{
		task1();
		}

	}
	if(distance>=95&&mode1==2&&mode2==0)
	{
		
		distance=0;
		Left_Speed_cnt=0;
		Right_Speed_cnt=0;
		mode1=3;
	}
		if(distance>=93&&mode1==2&&mode2==1)
	{
		
		distance=0;
		Left_Speed_cnt=0;
		Right_Speed_cnt=0;
		mode1=3;
	}
	if(mode1==3&&mode2==0)
	{
		angle_PID(130,130,-112);
		if(Yaw>=-118&&distance>=14)
		{
		mode1=4;
		
		}
	}
	if(mode1==3&&mode2==1)
	{
	angle_PID(130,130,-108);
		if(Yaw>=-114&&distance>=14)
		{
		mode1=4;
		
		}
	}
	if(mode1==4)
	{ if(Yaw>=-119&&Yaw<=-111)
		{
			angle_PID(130,130,-115);
		}
		else
		{
		task1();
		}
	}
	if(((left3+left4+left2+left1>=3)||distance>=97)&&mode1==4)
	{
		mode1=5;

	}
	
	if(mode1==5&&number==2)
	{
		angle_PID(130,130,5);
	}
 if(Yaw>=1&&mode1==5)
  {	distance=0;
		 Left_Speed_cnt=0;
		 Right_Speed_cnt=0;
     mode1=6;
//	if(mode2==1)
//	 {
//	 mode1=6;
//	 mode2=2;
//   }
   
  }
	if(mode1==5&&mode2==1)
	{
	mode1=6;
	mode2=2;
	
	}
	
  if(mode1==6&&mode2==0&&number==2)
  {
    mode1=0;
		mode2=1;
  }
	 if(mode1==5&&mode2==0&&number==1)
  {
    Motor_speed(0,0);
  }
 if(mode1==6&&mode2==2)
  {
   Motor_speed(0,0);
  }

}






void KUAIDIYITI2(void)
{ 
	if(mode1==0)
	{ 
		if(Yaw<=2&&Yaw>=-2)
	   {
			 angle_PID(50,50,0);
		 }
		 else
		 {
		 task2();
		 }
	}
	if(distance>=83&&mode1==0&&mode2==0)
	{
		mode1=1;
	}
	if(mode1==0&&mode2==1&&((left4+left2+left3>=2)))
	{
	
	mode1=1;
	
	}
	if(mode1==1)
	{  //	angle_PID(0,130,120);
			distance=0;
			Left_Speed_cnt=0;
			Right_Speed_cnt=0;
		  mode1=20;
	}
	if(mode1==20)
	{
		angle_PID(50,50,105);
		if(Yaw>=95)
		{
		mode1=2;
			
		}
	}

	if(mode1==2)
	{ 
		if(Yaw<=122&&Yaw>=118)
		{
		angle_PID(50,50,115);
		}
		else
		{
		task2();
		}

	}
	if(distance>=95&&mode1==2&&mode2==0)
	{
		
		distance=0;
		Left_Speed_cnt=0;
		Right_Speed_cnt=0;
		mode1=3;
	}
		if(distance>=93&&mode1==2&&mode2==1)
	{
		
		distance=0;
		Left_Speed_cnt=0;
		Right_Speed_cnt=0;
		mode1=3;
	}
	if(mode1==3&&mode2==0)
	{
		angle_PID(50,50,-116);
		if(Yaw>=-122&&distance>=14)
		{
		mode1=4;
		
		}
	}
	if(mode1==3&&mode2==1)
	{
	angle_PID(50,50,-119);
		if(Yaw>=-125&&distance>=14)
		{
		mode1=4;
		
		}
	}
	if(mode1==4)
	{ if(Yaw>=-121&&Yaw<=-113)
		{
			angle_PID(50,50,-117);
		}
		else
		{
		task2();
		}
	}
	if(((left3+left4+left2>=2)||distance>=93)&&mode1==4)
	{
		mode1=5;

	}
	
	if(mode1==5&&number==3)
	{
		angle_PID(30,30,-22);
	}
 if(Yaw>=-28&&mode1==5)
  {	distance=0;
		 Left_Speed_cnt=0;
		 Right_Speed_cnt=0;
     mode1=6;
//	if(mode2==1)
//	 {
//	 mode1=6;
//	 mode2=2;
//   }
   
  }
	if(mode1==5&&mode2==1)
	{
	mode1=6;
	mode2=2;
	
	}
	
  if(mode1==6&&mode2==0&&number==3)
  {
    mode1=0;
		mode2=1;
  }

 if(mode1==6&&mode2==2)
  {
   Motor_speed(0,0);
  }

}



