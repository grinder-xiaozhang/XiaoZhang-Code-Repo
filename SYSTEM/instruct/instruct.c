#include "instruct.h"
#include "Moter.h"
#include "increpid.h"
#include "Encoder.h" 

extern uint8_t Serial_RxData;
extern uint8_t Serial_RxFlag;
int16_t Left_speed;
int16_t Right_speed;

void instruct_control(void)
{
    // 如果串行接收标志（Serial_RxFlag）为真，即接收到数据
    if(Serial_RxFlag)
    {
        // 将串行接收标志复位，否则会一直为真
        Serial_RxFlag = 0;
        // 根据接收到的数据（Serial_RxData）来执行不同的动作
        switch (Serial_RxData)
        {
            // 如果接收到的字符是 'w'
            case 'w':
                // 设置电机速度（例如，两个电机都设置为50）

								Left_speed=50;
								Right_speed=50;
                Motor_speed(Left_speed,Right_speed);
                break;

            // 如果接收到的字符是 's'
            case 's':
                // 以相反的方向设置电机速度
                // 更改右编码器模式
                Right_Encoder_Init(0);
                // 更改左编码器模式
                Left_Encoder_Init(0);
								Left_speed=-50;
								Right_speed=-50;
                Motor_speed(Left_speed,Right_speed);
                break;

            // 如果接收到的字符是 'a'
            case 'a':
                // 设置电机速度，第一个电机速度为50，第二个电机速度为80
								Left_speed=50;
								Right_speed=80;
                Motor_speed(Left_speed,Right_speed);
                break;

            // 如果接收到的字符是 'd'
            case 'd':
                // 设置电机速度，第一个电机速度为80，第二个电机速度为50
								Left_speed=100;
								Right_speed=50;
                Motor_speed(Left_speed,Right_speed);
                break;

            // 如果接收到的字符是 't'
            case 't':
                // 停止
							  Left_speed=0;
								Right_speed=0;
								Motor_speed(Left_speed,Right_speed);
                break;
            case 'T':
                // 停止
                // 更改右编码器模式
                Right_Encoder_Init(1);
                // 更改左编码器模式
                Left_Encoder_Init(1);
							  Left_speed=0;
								Right_speed=0;
								Motor_speed(Left_speed,Right_speed);
                break;
            case 'q':
                // 更改左编码器模式
                Left_Encoder_Init(0);
                // 向左转圈
							  Left_speed=-50;
								Right_speed=50;
								Motor_speed(Left_speed,Right_speed);
                break;
            case 'e':
                // 更改右编码器模式
                Right_Encoder_Init(0);
                // 向右转圈
							  Left_speed=50;
								Right_speed=-50;
								Motor_speed(Left_speed,Right_speed);
                break;
        }
    }
     if(Left_speed>=0&&Right_speed>=0)
     {
        increment_PID(Left_speed,Right_speed);
     }
}
