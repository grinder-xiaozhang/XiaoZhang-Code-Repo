1.ʵ��Ŀ�ģ�
  �½�����STM32F4 �̼���V1.3.0�Ĺ���ģ��

2.ʵ������
  ���ؽ�������֮�󣬺��̵���˸

3.ע�����

 1���½����̵�ʱ����ȷ��Option for target->C/C++ѡ���ȫ���궨��Define������ַ���Ϊ��STM32F40_41xxx,USE_STDPERIPH_DRIVER
 
 
4.�ֲ��н��⵽����15��ʱ���main.cԴ�����£�

5.USART3 Emm_V5电机控制配置(PB10/PB11)：

   USART3_TX -> PB10
   USART3_RX -> PB11

   使用函数：
   Emm_V5_Vel_Control3(addr, dir, vel, acc, snF)  // 速度控制
   Emm_V5_Pos_Control3(addr, dir, vel, acc, clk, raF, snF)  // 位置控制

   初始化：在main函数中调用 uart3_init()
   示例：Emm_V5_Vel_Control3(1, 1, 100, 50, 0);  // 地址1，正向，速度100，加速度50

6.USART2 Emm_V5电机控制配置(PA2/PA3)：

   USART2_TX -> PA2
   USART2_RX -> PA3

   使用函数：
   Emm_V5_Vel_Control(addr, dir, vel, acc, snF)  // 速度控制
   Emm_V5_Pos_Control(addr, dir, vel, acc, clk, raF, snF)  // 位置控制

   初始化：在main函数中调用 uart2_init()
   示例：Emm_V5_Vel_Control(2, 1, 100, 50, 0);  // 地址2，正向，速度100，加速度50





#include "stm32f4xx.h"


//ALIENTEK ̽����STM32F407������ ʵ��0
//STM32F4����ģ��-�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com
//�������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK
  
void Delay(__IO uint32_t nCount);

void Delay(__IO uint32_t nCount)
{
  while(nCount--){}
}

int main(void)
{

  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOF, &GPIO_InitStructure);

  while(1){
		GPIO_SetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_10);
		Delay(0x7FFFFF);
		GPIO_ResetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_10);
		Delay(0x7FFFFF);
	
	}
}
