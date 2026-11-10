#include "stm32f4xx.h"                  // Device header

void Motor_Init(void)
{      
    // 定义一个GPIO初始化结构体
    GPIO_InitTypeDef GPIO_InitStructstr;
    // 使能GPIOD端口的时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    // 设置GPIO_InitStructstr结构体中的引脚位，这里选择的是GPIOD端口的4、5、6、7号引脚
    GPIO_InitStructstr.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    // 设置GPIO模式为输出模式
    GPIO_InitStructstr.GPIO_Mode = GPIO_Mode_OUT;
    // 设置GPIO输出类型为推挽输出
    GPIO_InitStructstr.GPIO_OType = GPIO_OType_PP;
    // 设置GPIO上拉/下拉为上拉
    GPIO_InitStructstr.GPIO_PuPd = GPIO_PuPd_UP;
    // 设置GPIO输出速度为100MHz
    GPIO_InitStructstr.GPIO_Speed = GPIO_Speed_100MHz;
    // 使用上面定义的参数初始化GPIOD端口的对应引脚
    GPIO_Init(GPIOD, &GPIO_InitStructstr);
    // 将GPIOD端口的4、5、6、7号引脚复位（即设置为低电平）
    GPIO_ResetBits(GPIOD, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
}

void Motor_PWM_Init(void)
{		 					 
	// 定义GPIO和TIM的初始化结构体变量
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	// 使能TIM2的时钟，以便能够对其进行配置
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  

	// 使能GPIOA和GPIOB的时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE); 

	// 将GPIOA的15号引脚复用为TIM2的PWM输出
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource15,GPIO_AF_TIM2); 

	// 将GPIOB的3号引脚复用为TIM2的PWM输出（替代原来的PA2）
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_TIM2); 

	// 配置GPIOA的15号引脚为复用功能输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;           
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        
	GPIO_Init(GPIOA,&GPIO_InitStructure);             
	
	// 配置GPIOB的3号引脚为复用功能输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;           
	GPIO_Init(GPIOB,&GPIO_InitStructure);              

	// 配置TIM2的基本参数：分频系数、计数模式、自动重装载值、时钟分频
	TIM_TimeBaseStructure.TIM_Prescaler=107;  //psc
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseStructure.TIM_Period=320;   //arr
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 

	// 根据上述参数初始化TIM2
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);

	// 初始化TIM2的Channel1为PWM模式 (PA15)
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);  

	// 使能TIM2的Channel1的预装载功能
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  

	// 初始化TIM2的Channel2为PWM模式 (PB3，替代原来的CH3)
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);  

	// 使能TIM2的Channel2的预装载功能
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  

	// 使能TIM2的自动重装载预装载功能
	TIM_ARRPreloadConfig(TIM2,ENABLE);

	// 使能TIM2
	TIM_Cmd(TIM2, ENABLE);
}  

void Motor_speed(int16_t left,int16_t right)
{
	if(left>=0)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_4); 
		GPIO_ResetBits(GPIOD, GPIO_Pin_5);
		TIM_SetCompare2(TIM2, left); 
	}
	else if(left<0)
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_4);
		GPIO_SetBits(GPIOD, GPIO_Pin_5);
		TIM_SetCompare2(TIM2, -left); 
	}

	if(right>=0)
	{
		// 设置GPIOD的Pin_6为高电平，用于控制右轮
		GPIO_SetBits(GPIOD, GPIO_Pin_6); 
		// 设置GPIOA的Pin_7为低电平，用于控制右轮
		GPIO_ResetBits(GPIOD, GPIO_Pin_7);
		// 设置TIM2定时器的比较值1为right，用于控制右轮的转速
		TIM_SetCompare1(TIM2, right);
	}
	else if(right<0)
	{
		// 设置GPIOD的Pin_6为低电平，用于控制右轮
		GPIO_ResetBits(GPIOD, GPIO_Pin_6); 
		// 设置GPIOA的Pin_7为高电平，用于控制右轮
		GPIO_SetBits(GPIOD, GPIO_Pin_7);
		// 设置TIM2定时器的比较值1为right，用于控制右轮的转速
		TIM_SetCompare1(TIM2, -right);
	}
}



