/*
							 _ooOoo_
							o8888888o
							88" . "88
							(| -_- |)
							O\  =  /O
					 ____/`---'\____
				 .'  \\|     |//  `.
				/  \\|||  :  |||//  \
		   /  _||||| -:- |||||-  \
		   |   | \\\  -  /// |   |
		   | \_|  ''\---/''  |   |
		   \  .-\__  `-`  ___/-. /
		 ___`. .'  /--.--\  `. . __
	  ."" '<  `.___\_<|>_/___.'  >'"".
	 | | :  `- \`.;`\ _ /`;.`/ - ` : | |
	 \  \ `-.   \_ __\ /__ _/   .-` /  /
======`-.____`-.___\_____/___.-`____.-'======
				   `=---='
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		 ���汣��       ����BUG
*/
#include "stm32f4xx.h"
#include "sys.h"
#include "board.h"
#include "delay.h"
#include "usart.h"
#include "Emm_V5.h"
#include "UART_maxcam.h"
#include <math.h>
#define PI 3.1415926f
// PID参数
//#define KP 0.000040f//0.000027f
//#define KI 0.0024f
//#define KD 0.0045f
//#define KP 0.0001f//0.000027f
//#define KI 0.0024f
//#define KD 0.50045f
#define KP 2.8f//0.000027f
#define KI 0.87f
#define KD 0.40f
//#define KP1 0.000050f//0.000027f
//#define KI1 0.00255f
//#define KD1 0.0027f
#define KP1  0.3f       //0.000050f//0.000027f
#define KI1 0.00245f
#define KD1 0.003f
#define KP_SPD 0.9f
#define KI_SPD 0.02f
#define KD_SPD 0.01f
#define MAX_PULSE_STEP 50
#define MAX_XZ 3.0f
#define MAX_JULI 1000
//#define ANGLE_LIMIT_X 91.78f
#define ANGLE_LIMIT_X  90.0f// 80.10f
#define ANGLE_LIMIT_Y 90.0f//80.10f
#define KP_SPD 0.95f
#define KI_SPD 0.02f
#define KD_SPD 0.01f
//#define MAX_PULSE_STEP  40    // 位置平滑最大步长
#define MAX_SPD_TAR     60    // 位置环输出最大目标速度
#define MAX_SPD_OUT     30    // 速度环单帧最大脉冲增量
// PID静态缓存
static float smooth_pulse = 0.0f;
static long pulse_integral = 0;
static int last_err = 0;
static uint8_t pid_init_flag = 1;
int last_pos;           // 上一帧输出位置
float spd_integral;     // 速度环积分
int last_spd_err;       // 速度环上次误差
// 原有滤波变量
static float smooth_x = 0.0f;
static float last_raw_x = 0.0f;
static uint8_t x_init_flag = 1;
static float smooth_y = 0.0f;
static float last_raw_y = 0.0f;
static uint8_t y_init_flag = 1;
//���ڴ洢�Ҳ���ٶ�ֵ
int Right_Speed = 0;
int Left_Speed = 0;
//���ڴ洢���н��յ�������
uint8_t Serial_RxData;
//�������н������ݵı�־λ
uint8_t Serial_RxFlag;
uint8_t buffer[9];     //���ݻ�����
uint8_t RxData_Cnt;    //���ݳ���
int Yaw; 
uint8_t need_motor_update = 0;  // 电机更新标志
char str[30] = "";
uint8_t com_data; 
uint8_t RxBuffer1[4]={0};
uint8_t RxCounter1=0;
uint8_t RxState = 0;	
uint8_t Header1=0,Header2=0,x=0,frame=0;
uint8_t cx,cy;
uint16_t cnttt;
uint16_t cnttt1,cnttt2;
double distance;
double distance2=0;
double distance3=0;
int Left_Speed_cnt = 0;
int Right_Speed_cnt = 0;
int xmode1,ymode1,zmode1,amode1,cmode1=0;
int a,b,c,d,e,f=0;
float goal_smooth=0;
float last_goal_smooth=0;
float ennagle=0;
float last_ennagle=0;
float goal_ennagle=0;
float rad=0;
float yennagle=0;
float ylast_ennagle=0;
float ygoal_ennagle=0;
float yrad=0;
float smooth_ennagle_x,smooth_ennagle_y,pulse_target,pulse_target_y=0;
extern uint8_t main_mode,mode2,mode1,flag,flag_z,number;
float ennagle_x,ennagle_y,last_ennagle_x,last_ennagle_y,add_x=0;
//float PulsePID_X(float pulse_target)
//{
//    if(pid_init_flag)
//    {
//        smooth_pulse = pulse_target;
//        pulse_integral = 0;
//        last_err = 0;
//        pid_init_flag = 0;
//        return pulse_target;
//    }

//    // 一阶平滑滤波
//    smooth_pulse = 0.87f * smooth_pulse + 0.13f * pulse_target;
//    int tar_int = (int)roundf(smooth_pulse);

//    // 限制单帧脉冲最大变化幅度，防止电机猛跳
//    int delta = tar_int - (int)smooth_pulse;
//    if(delta > MAX_PULSE_STEP) tar_int = (int)smooth_pulse + MAX_PULSE_STEP;
//    if(delta < -MAX_PULSE_STEP) tar_int = (int)smooth_pulse - MAX_PULSE_STEP;

//    // PID误差计算
//    int err = tar_int - (int)smooth_pulse;
//    pulse_integral += err;
//    // 积分限幅防饱和
////    if(pulse_integral > 800)  pulse_integral = 800;
////    if(pulse_integral < -800) pulse_integral = -800;
//		if(pulse_integral > 500)  pulse_integral = 500;
//    if(pulse_integral < -500) pulse_integral = -500;
//		
//    int err_diff = err - last_err;
//    float pid_out = KP * err + KI * pulse_integral + KD * err_diff;

//    // 单次修正幅度限制
//    int adjust = (int)pid_out;
//    if(adjust > 25) adjust = 25;
//    if(adjust < -25) adjust = -25;

//    last_err = err;
//    return tar_int + adjust;
//}
//float PulsePID_X(float pulse_target)
//{
//    if(pid_init_flag)
//    {
//        smooth_pulse = pulse_target;
//        pulse_integral = 0;
//        last_err = 0;
//        last_pos = (int)roundf(pulse_target);

//        // 速度环初始化
//        spd_integral = 0;
//        last_spd_err = 0;
//        pid_init_flag = 0;
//        return pulse_target;
//    }

//    // 一阶平滑滤波目标位置
//    smooth_pulse = 0.84f * smooth_pulse + 0.16f * pulse_target;
//    int tar_int = (int)roundf(smooth_pulse);

//    // 【修复原bug】限制单帧目标位置变化幅度（对比上一次输出位置）
//    int delta_pos = tar_int - last_pos;
//    if(delta_pos > MAX_PULSE_STEP)
//        tar_int = last_pos + MAX_PULSE_STEP;
//    if(delta_pos < -MAX_PULSE_STEP)
//        tar_int = last_pos - MAX_PULSE_STEP;

//    // ========== 外环：位置PID，输出目标速度 ==========
//    int pos_err = tar_int - last_pos;
//    pulse_integral += pos_err;
//    // 积分限幅
//    if(pulse_integral > 500)  pulse_integral = 500;
//    if(pulse_integral < -500) pulse_integral = -500;

//    int err_diff = pos_err - last_err;
//    float pos_pid_out = KP * pos_err + KI * pulse_integral + KD * err_diff;

//    // 位置环输出 = 目标速度，限幅最大速度
//    int tar_speed = (int)pos_pid_out;
//    if(tar_speed > MAX_SPD_TAR)  tar_speed = MAX_SPD_TAR;
//    if(tar_speed < -MAX_SPD_TAR) tar_speed = -MAX_SPD_TAR;
//    last_err = pos_err;

//    // ========== 内环：速度PID ==========
//    // 计算当前实际速度：当前输出 - 上一帧输出
//    int real_speed = tar_int - last_pos;
//    int spd_err = tar_speed - real_speed;

//    spd_integral += spd_err;
//    // 速度积分限幅
//    if(spd_integral > 300)  spd_integral = 300;
//    if(spd_integral < -300) spd_integral = -300;

//    int spd_err_diff = spd_err - last_spd_err;
//    float spd_pid_out = KP_SPD * spd_err + KI_SPD * spd_integral + KD_SPD * spd_err_diff;

//    // 速度输出限幅
//    int spd_adjust = (int)spd_pid_out;
//    if(spd_adjust > MAX_SPD_OUT)  spd_adjust = MAX_SPD_OUT;
//    if(spd_adjust < -MAX_SPD_OUT) spd_adjust = -MAX_SPD_OUT;
//    last_spd_err = spd_err;

//    // 最终输出脉冲位置
//    int final_out = last_pos + spd_adjust;
//    last_pos = final_out;

//    return (float)final_out;
//}

float PulsePID_X(float pulse_target)
{
    if(pid_init_flag)
    {
        smooth_pulse = pulse_target;
        pulse_integral = 0;
        last_err = 0;
        last_pos = (int)roundf(pulse_target);

        // 速度环初始化
        spd_integral = 0;
        last_spd_err = 0;
        pid_init_flag = 0;
        return pulse_target;
    }

    // 一阶平滑滤波目标位置
    smooth_pulse = 0.84f * smooth_pulse + 0.16f * pulse_target;
    int tar_int = (int)roundf(smooth_pulse);

    // ========== 新增修复：目标置0直接清空双积分，消除积分漂移 ==========
    if(pulse_target == 0.0f)
    {
        pulse_integral = 0;
        spd_integral = 0;
    }

    // 限制单帧目标位置变化幅度
    int delta_pos = tar_int - last_pos;
    if(delta_pos > MAX_PULSE_STEP)
        tar_int = last_pos + MAX_PULSE_STEP;
    if(delta_pos < -MAX_PULSE_STEP)
        tar_int = last_pos - MAX_PULSE_STEP;

    // ========== 外环：位置PID，输出目标速度 ==========
    int pos_err = tar_int - last_pos;
    pulse_integral += pos_err;
    // 积分限幅
    if(pulse_integral > 500)  pulse_integral = 500;
    if(pulse_integral < -500) pulse_integral = -500;

    int err_diff = pos_err - last_err;
    float pos_pid_out = KP * pos_err + KI * pulse_integral + KD * err_diff;

    // 位置环输出 = 目标速度，限幅最大速度
    int tar_speed = (int)pos_pid_out;
    if(tar_speed > MAX_SPD_TAR)  tar_speed = MAX_SPD_TAR;
    if(tar_speed < -MAX_SPD_TAR) tar_speed = -MAX_SPD_TAR;
    last_err = pos_err;

    // ========== 内环：速度PID ==========
    int real_speed = tar_int - last_pos;
    int spd_err = tar_speed - real_speed;

    spd_integral += spd_err;
    if(spd_integral > 300)  spd_integral = 300;
    if(spd_integral < -300) spd_integral = -300;

    int spd_err_diff = spd_err - last_spd_err;
    float spd_pid_out = KP_SPD * spd_err + KI_SPD * spd_integral + KD_SPD * spd_err_diff;

    // 速度输出限幅
    int spd_adjust = (int)spd_pid_out;
    if(spd_adjust > MAX_SPD_OUT)  spd_adjust = MAX_SPD_OUT;
    if(spd_adjust < -MAX_SPD_OUT) spd_adjust = -MAX_SPD_OUT;
    last_spd_err = spd_err;

    // 最终输出脉冲位置
    int final_out = last_pos + spd_adjust;
    last_pos = final_out;

    return (float)final_out;
}


float PulsePID_Y(float pulse_target)
{
    if(pid_init_flag)
    {
        smooth_pulse = pulse_target;
        pulse_integral = 0;
        last_err = 0;
        pid_init_flag = 0;
        return pulse_target;
    }

    // 一阶平滑滤波
    smooth_pulse = 0.87f * smooth_pulse + 0.13f * pulse_target;
    int tar_int = (int)roundf(smooth_pulse);

    // 限制单帧脉冲最大变化幅度，防止电机猛跳
    int delta = tar_int - (int)smooth_pulse;
    if(delta > MAX_PULSE_STEP) tar_int = (int)smooth_pulse + MAX_PULSE_STEP;
    if(delta < -MAX_PULSE_STEP) tar_int = (int)smooth_pulse - MAX_PULSE_STEP;

    // PID误差计算
    int err = tar_int - (int)smooth_pulse;
    pulse_integral += err;
    // 积分限幅防饱和
    if(pulse_integral > 800)  pulse_integral = 800;
    if(pulse_integral < -800) pulse_integral = -800;

    int err_diff = err - last_err;
    float pid_out = KP1 * err + KI1 * pulse_integral + KD1 * err_diff;

    // 单次修正幅度限制
    int adjust = (int)pid_out;
    if(adjust > 25) adjust = 25;
    if(adjust < -25) adjust = -25;

    last_err = err;
    return tar_int + adjust;
}

void ennmotor(void)
{
    Uart5_ProcessData();
    int16_t x_target = Uart5_getdata(1);
    int16_t y_target = Uart5_getdata(2);

    // 1.计算原始角度ennagle_x
    float rad  = atan2(300, (float)x_target-5);//130
	  float yrad  = atan2(900, (float)y_target-3);//130
    float ennagle_x = rad  * 180.0f / PI;
    float ennagle_y = yrad  * 180.0f / PI;
    // 2.【明确定义 pulse_target 变量】ennagle_x ×8.88
		if(fabs(x_target)<20)
	{
	add_x=0;
	}
	if(fabs(x_target)>=20)
	{
	add_x=7;
	}
if(fabs(ennagle_x-last_ennagle_x)>=0.10f)
  {

						if(ennagle_x-ANGLE_LIMIT_X>=0)
			{
			pulse_target = (ennagle_x-ANGLE_LIMIT_X) * 16.8f;
			}
    // 3.将 pulse_target 送入PID计
				else if(ennagle_x-ANGLE_LIMIT_X<0)
			{
			pulse_target = (ANGLE_LIMIT_X-ennagle_x) * 16.8f;
			}
	}
	else	if(ennagle_x-last_ennagle_x<0.10f)
	{
	
	pulse_target=0;
	
	}
	if(fabs(ennagle_y-last_ennagle_y)>=0.10f)
	{	
		if(ennagle_y-ANGLE_LIMIT_Y>=0)
		{
		 pulse_target_y = (ennagle_y-ANGLE_LIMIT_Y) * 16.8f;
		}
			// 3.将 pulse_target 送入PID计
			else if(ennagle_y-ANGLE_LIMIT_Y<0)
		{
		 pulse_target_y = (ANGLE_LIMIT_Y-ennagle_y) * 16.8f;
		}
	}
	if(fabs(ennagle_y-last_ennagle_y)<=0.10f)
	{
	
		pulse_target_y=0;
	
	}
	      last_ennagle_x=ennagle_x;
		    last_ennagle_y=ennagle_y;
	float pulse_after_pid = PulsePID_X(pulse_target);
  
    // 4.PID处理后的脉冲反向换算为角度，赋值给smooth_ennagle_x
    smooth_ennagle_x = pulse_after_pid ;
    smooth_ennagle_y =PulsePID_Y(pulse_target_y);
    // 原有电机控制逻辑不变，直接调用smooth_ennagle_x
	
    if(ennagle_x>=ANGLE_LIMIT_X)
    {
        Emm_V5_Vel_Control(1,0,(smooth_ennagle_x*0.16f)+add_x,100,0);//0.1f
    }
    else if(ennagle_x<ANGLE_LIMIT_X)
    { 
        Emm_V5_Vel_Control(1,1,(smooth_ennagle_x*0.16f)+add_x,100,0);//0.1f
    }
		    if(ennagle_y>=ANGLE_LIMIT_Y)
    {
      Emm_V5_Vel_Control3(2,1,smooth_ennagle_y*0.072f,60,0);
    }
    else if(ennagle_y<ANGLE_LIMIT_Y)
    { 
        Emm_V5_Vel_Control3(2,0,smooth_ennagle_y*0.072f,60,0);
    }
				
}

int main(void)
{
	// ��ʼ��OLED��ʾ��

	OLED_Init();
	Key_Init();
	EXTIXa_Init();
	// ��ʼ����ʱ��4
	TIMer4_Init();
	TIMer2_Init();
	TIMer6_Init();
	// ��ʼ������ӿ�
	Motor_Init();
	// ��ʼ�����PWM���ƣ����õ��Ƶ��Ϊ10KHZ
	Motor_PWM_Init();
	// ��ʼ���������
	Left_Encoder_Init();
	// ��ʼ���ұ�����
	Right_Encoder_Init();
	// ��ʼ��UART1
	uart1_init();
	uart2_init();
	uart3_init();
	LED_Init();
	Uart5_en_Init();
	board_init();
	delay_ms(500);
		if(Yaw!=0)
		{
			setJy92_Yaw_Zero();
		}
    while(1)
	{
//    Uart5_ProcessData();
//    int16_t x_target = Uart5_getdata(1);
//    int16_t y_target = Uart5_getdata(2);

//    // 1.计算原始角度ennagle_x
//    float rad  = atan2(800, (float)x_target);
//	  float yrad  = atan2(500, (float)y_target);
//    float ennagle_x = rad  * 180.0f / PI;
//    float ennagle_y = yrad  * 180.0f / PI;
//    // 2.【明确定义 pulse_target 变量】ennagle_x ×8.88
//	if(ennagle_x-90>=0)
//	{
// pulse_target = (ennagle_x-90) * 16.8f;
//  }
//    // 3.将 pulse_target 送入PID计
//   	else if(ennagle_x-90<0)
//	{
//  pulse_target = (90-ennagle_x) * 16.8f;
//  }
//	if(ennagle_y-90>=0)
//	{
//   pulse_target_y = (ennagle_y-90) * 16.8f;
//  }
//    // 3.将 pulse_target 送入PID计
//   	else if(ennagle_y-90<0)
//	{
//   pulse_target_y = (90-ennagle_y) * 16.8f;
//  }

//	float pulse_after_pid = PulsePID_X(pulse_target);
//  
//    // 4.PID处理后的脉冲反向换算为角度，赋值给smooth_ennagle_x
//    smooth_ennagle_x = pulse_after_pid ;
//    smooth_ennagle_y =PulsePID_Y(pulse_target_y);
		OLED_Refresh();                         // ˢ��OLED��ʾ��
		sprintf(str, "L:%d       \r\n",Yaw);
		OLED_ShowString(0, 0, (uint8_t *)str, 16); // 8*16 ��ABC��
		sprintf(str, "b:%d      \r\n",(uint16_t)15 );
		OLED_ShowString(0, 16, (uint8_t *)str, 16); // 8*16 ��ABC��
		sprintf(str, "x:%d      \r\n",mode1);
		OLED_ShowString(0, 32, (uint8_t *)str, 16); // 8*16 ��ABC��
//		sprintf(str, "M:%d      \r\n", mode2);
//		OLED_ShowString(32, 48, (uint8_t *)str, 16); // 8*16 ��ABC��		
//		sprintf(str, "D2:%d      \r\n", (uint16_t)distance2);
//		OLED_ShowString(0, 16, (uint8_t *)str, 16); // 8*16 ��ABC��	
		
		sprintf(str, "D:%d      \r\n",number);
		OLED_ShowString(0, 48, (uint8_t *)str, 16); // 8*16 ��ABC��	
		
		if( main_mode == 2)
		{ 
			ennmotor();
			

		}
}
	}




void TIM2_IRQHandler(void)//TIM2�жϷ�����
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==1)
	{
	if(main_mode==1)
		{



    }
		

	if(main_mode==2)
		{
     
		}

	if(main_mode==3)
	{
  KUAIDIYITI2();
	}

}


	

	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//����жϱ�־λ
}

void TIM6_DAC_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)==1)
	{
		

	}
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
}


void TIM4_IRQHandler(void)//TIM4�жϷ�����
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==1)
	{	
	Left_Speed =(short)TIM_GetCounter(TIM5);  // �ɼ��������ļ���ֵ������;
	Right_Speed =(short)TIM_GetCounter(TIM3);  // �ɼ��������ļ���ֵ������;
	Left_Speed_cnt+=Left_Speed;
	Right_Speed_cnt+=Right_Speed;
	distance=Count_Distance((Left_Speed_cnt+Right_Speed_cnt)/2);
		if(Left_Speed!=0||Right_Speed!=0)
		{
			TIM_SetCounter(TIM5,0);
			TIM_SetCounter(TIM3,0);
		}
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);//����жϱ�־λ
}


void USART1_IRQHandler(void) 
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		Serial_RxData = USART_ReceiveData(USART1);
        if (Serial_RxFlag == 0 && Serial_RxData == 0x55)
        {
            Serial_RxFlag = 1;
        }
         else if(Serial_RxFlag==1&&Serial_RxData==0x53)
        {
            Serial_RxFlag=6;
        }
        else if(Serial_RxFlag==6)
        {
						buffer[RxData_Cnt++]=Serial_RxData;
						if(RxData_Cnt==9)
						{
								if((uint8_t)(buffer[0]+buffer[1]+buffer[2]+buffer[3]+buffer[4]+buffer[5]+buffer[6]+buffer[7]+0xa8)==buffer[8])
								{
									Yaw=((short)((short)(buffer[5]<<8)|buffer[4]))*0.0054931640625f;
								}
								RxData_Cnt=0;
								Serial_RxFlag=0;
						}
        }
        else
        {
            Serial_RxFlag=0;
            RxData_Cnt=0;
        }
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}
	
//void ennmotor(void)
//{
////    Uart5_ProcessData();
////		int16_t x_target = Uart5_getdata(1);
////		int16_t y_target = Uart5_getdata(2);
////    rad= atan2(40, x_target);
////	  ennagle=rad * 180.0f / PI;
////	if(ennagle>0)
////	{
////		Emm_V5_Pos_Control(1,0,500,0,ennagle,1,0);
////	}
////   if(ennagle<0)
////	 {
////	 		Emm_V5_Pos_Control(1,0,500,0,-ennagle,1,0);

////	 }
//Emm_V5_Pos_Control(1,0,500,0,Yaw,1,0);

//}


//void USART3_IRQHandler(void)
//{	
//	
//	 if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
//    {
//        com_data = USART_ReceiveData(USART3);
//        
//        // �жϽ��յ����Ƿ�ΪASCII���֣�'0'-'9'��
//        if(com_data >= '0' && com_data <= '9')
//        {
//            // ��ASCII��ת��Ϊ����
//            x = com_data - '0';
//            
//            // ��������������Ӧ��ģʽ
//            if(x >= 1 && x <= 8)
//            {
//                main_mode = 1;    // ������ģʽ
//                mode1 = 0;        // ������ģʽ
//                distance = 0;     // ���þ���
//                Left_Speed_cnt = 0;
//                Right_Speed_cnt = 0;
//                
//                // ��ʾ����LEDָʾģʽ���л�
//                LED0 = !LED0;
//                BEEP = 1;
//                delay_ms(100);
//                BEEP = 0;
//            }
//            else
//            {
//                // ��Чģʽֵ
//                main_mode = 0;
//            }
//        }
//        
//        USART_ClearITPendingBit(USART3, USART_IT_RXNE);
//    }
//}	
	

	
//	// ���USART3�Ľ����ж��Ƿ�����
//	if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
//	{
//		// ��USART2��������
//		com_data = USART_ReceiveData(USART3);

//		// ���ݽ��յ������ݺ͵�ǰ�Ľ���״̬��RxState������������
//		if(RxState == 0 && com_data == 0xA5)  // �����ǰ״̬Ϊ0�ҽ��յ�������Ϊ0xA5
//		{
//			RxState = 1;                     // ��״̬����Ϊ1
//			RxBuffer1[RxCounter1++] = com_data; // �����յ������ݴ��뻺�����������¼�����
//		}
//		else if(RxState == 1 && com_data == 0xA6)  // �����ǰ״̬Ϊ1�ҽ��յ�������Ϊ0xA6
//		{
//			RxState = 2;                     // ��״̬����Ϊ2
//			RxBuffer1[RxCounter1++] = com_data; // �����յ������ݴ��뻺�����������¼�����
//		}
//		else if(RxState == 2)  // �����ǰ״̬Ϊ2
//		{
//			RxBuffer1[RxCounter1++] = com_data; // �����յ������ݴ��뻺�����������¼�����
//			if(com_data == 0x5B)  // ������յ�������Ϊ0x5B
//			{
//				RxState = 3;                 // ��״̬����Ϊ3
//			}
//		}

//		// ������յ�������Ϊ0x5B�ҵ�ǰ״̬Ϊ3
//		if(com_data == 0x5B && RxState == 3)
//		{
//			// ����������ǰ6�����ݷֱ�ֵ
//			Header1 = RxBuffer1[0];
//			Header2 = RxBuffer1[1];
//			x = RxBuffer1[2];
//			frame = RxBuffer1[3];
//			// ���ý���״̬�ͼ�����
//			RxState = 0;
//			RxCounter1 = 0;
//		}

//		// ���USART2�Ľ����жϱ�־λ
//		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
//	}

