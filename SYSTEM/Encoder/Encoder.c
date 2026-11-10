#include "stm32f4xx.h"                  // Device header
#include "Encoder.h" 

void Left_Encoder_Init(void)
{
	// 定义定时器、GPIO和输入捕获的初始化结构体
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;

	// 1. 时钟配置
	// 开启定时器5的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5 ,ENABLE);
	// 开启GPIOA的时钟
	RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOA ,ENABLE);
	// 设置GPIOA的PA0和PA1引脚为定时器5的复用功能
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5);

	// 2. GPIO配置
	// 初始化GPIO结构体
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;           // 复用功能模式
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;  // PA0和PA1引脚
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;       // 引脚速度为50MHz
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;          // 开漏输出
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;           // 内部上拉
	// 应用GPIO配置到GPIOA
	GPIO_Init(GPIOA ,&GPIO_InitStruct);

	// 3. 定时器配置
	// 初始化定时器结构体
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
	// 设置定时器不分频
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	// 设置定时器为向上计数模式
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	// 设置定时器重装载值为65535
	TIM_TimeBaseInitStruct.TIM_Period = 65535;
	// 设置定时器预分频系数为0
	TIM_TimeBaseInitStruct.TIM_Prescaler = 0;
	// 应用定时器配置到TIM5
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStruct);

	// 4. 编码器配置: 定时器5，模式3，上升沿
	// 设置TIM5为编码器模式3，TI12通道，上升沿触发

	TIM_EncoderInterfaceConfig(TIM5,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);

	// 5. 输入捕获配置
	// 初始化输入捕获结构体
	TIM_ICStructInit(&TIM_ICInitStruct);
	// 设置输入捕获滤波器为10
	TIM_ICInitStruct.TIM_ICFilter = 10;
	// 应用输入捕获配置到TIM5
	TIM_ICInit(TIM5,&TIM_ICInitStruct);

	// 6. 清除定时器溢出更新标志位(清除计数值)
	// 清除TIM5的更新标志位
	TIM_ClearFlag(TIM5,TIM_FLAG_Update);

	// 7. 定时器5，溢出更新，使能
	// 使能TIM5的溢出更新中断
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);

	// 8. 定时数据清零(输入捕获的值从0开始计数)
	// 重置TIM5的计数值为0
	TIM_SetCounter(TIM5,0);

	// 9. 定时器2使能
	// 启用TIM5定时器
	TIM_Cmd(TIM5,ENABLE);                   
}

void Right_Encoder_Init(void)
{
	// 声明定时器和GPIO的初始化结构体
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;

	// 1. 时钟配置
	// 开启TIM3定时器的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	// 开启GPIOA的时钟
	RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	// 配置PA6和PA7引脚为TIM4的复用功能
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM4);

	// 2. GPIO配置
	// 初始化GPIO结构体
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;  // PA6和PA7
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	// 根据上述配置初始化GPIOA
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	// 3. 定时器配置
	// 初始化定时器结构体
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
	// 设置定时器不分频
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	// 设置定时器为向上计数模式
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	// 设置定时器重载值为65535
	TIM_TimeBaseInitStruct.TIM_Period = 65535;
	// 设置定时器预分频系数为0
	TIM_TimeBaseInitStruct.TIM_Prescaler = 0;
	// 根据上述配置初始化TIM3定时器
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);

	// 4. 编码器配置: 使用TIM3定时器，模式3，上升沿触发
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);

	// 5. 输入捕获配置
	// 初始化输入捕获结构体
	TIM_ICStructInit(&TIM_ICInitStruct);
	// 设置输入捕获滤波器为10
	TIM_ICInitStruct.TIM_ICFilter = 10;
	// 根据上述配置初始化TIM3的输入捕获
	TIM_ICInit(TIM3, &TIM_ICInitStruct);

	// 6. 清除TIM3定时器的更新标志位（清除计数值）
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);

	// 7. 使能TIM3定时器的更新中断
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	// 8. 重置TIM3定时器的计数值为0
	TIM_SetCounter(TIM3, 0);

	// 9. 使能TIM3定时器
	TIM_Cmd(TIM3, ENABLE);             
}
