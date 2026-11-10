#ifndef __OLED_H
#define __OLED_H 
#include "stm32f4xx.h" 
#include "stdlib.h"	

//-----------------OLED�˿ڶ���----------------

#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOD,GPIO_Pin_0)//SCL
#define OLED_SCLK_Set() GPIO_SetBits(GPIOD,GPIO_Pin_0)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOD,GPIO_Pin_1)//DIN
#define OLED_SDIN_Set() GPIO_SetBits(GPIOD,GPIO_Pin_1)



#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����
#define u8 unsigned char
#define u32 unsigned int

// 清除OLED屏幕上的某个点
void OLED_ClearPoint(u8 x,u8 y);
// 切换OLED的颜色显示模式
void OLED_ColorTurn(u8 i);
// 切换OLED的显示模式
void OLED_DisplayTurn(u8 i);
// 启动I2C通信
void I2C_Start(void);
// 停止I2C通信
void I2C_Stop(void);
// 等待I2C的应答信号
void I2C_WaitAck(void);
// 发送一个字节的数据
void Send_Byte(u8 dat);
// 向OLED写入一个字节的数据，cmd为0表示写入命令，为1表示写入数据
void OLED_WR_Byte(u8 dat,u8 cmd);
// 打开OLED显示
void OLED_DisPlay_On(void);
// 关闭OLED显示
void OLED_DisPlay_Off(void);
// 刷新OLED显示
void OLED_Refresh(void);
// 清空OLED屏幕
void OLED_Clear(void);
// 在OLED屏幕上绘制一个点
void OLED_DrawPoint(u8 x,u8 y);
// 在OLED屏幕上绘制一条线
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2);
// 在OLED屏幕上绘制一个圆
void OLED_DrawCircle(u8 x,u8 y,u8 r);
// 在OLED屏幕上显示一个字符
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1);
// 在OLED屏幕上显示一个字符串
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1);
// 在OLED屏幕上显示一个数字
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1);
// 在OLED屏幕上显示一个中文字符
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1);
// OLED滚动显示
void OLED_ScrollDisplay(u8 num,u8 space);
// 设置OLED的当前写入位置
void OLED_WR_BP(u8 x,u8 y);
// 在OLED屏幕上显示一张图片
void OLED_ShowPicture(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[]);
// 初始化OLED
void OLED_Init(void);
#endif

