#include "stm32f4xx.h"                  // Device header
#include "Timer.h" 

void TIMer4_Init(void)
{
	// ����һ��NVIC��ʼ���ṹ�����
	NVIC_InitTypeDef  NVIC_InitStructure;

	// ����һ����ʱ��ʱ���׼��ʼ���ṹ�����
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

	// ʹ��APB1ʱ�ӣ��Ա�ʹ��TIM4��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

	// ����TIM4��ʱ����ʱ���׼����
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; // ����ʱ�ӷ�Ƶ����Ϊ1
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // ���ü���ģʽΪ���ϼ���
	TIM_TimeBaseInitStructure.TIM_Period = 20000-1; // �����Զ���װ��ֵΪ10000-1
	TIM_TimeBaseInitStructure.TIM_Prescaler = 144-1; // ����Ԥ��ƵֵΪ144-1

	// ʹ��ǰ�����õ�ʱ���׼������ʼ��TIM4��ʱ��
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);

	// ����NVIC�жϿ������������Ա�TIM4��ʱ���жϿ��Ա���Ӧ
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; // �����ж�ͨ��ΪTIM4��ʱ���ж�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // ʹ�ܸ��ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; // ������ռ���ȼ�Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; // ���������ȼ�Ϊ2

	// ʹ��ǰ�����õ�NVIC������ʼ��NVIC�жϿ�����
	NVIC_Init(&NVIC_InitStructure);

	// ʹ��TIM4��ʱ�����жϸ��¹���
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

	// ʹ��TIM4��ʱ��
	TIM_Cmd(TIM4, ENABLE);
}

void TIMer2_Init(void)
{
	// ����һ��NVIC��ʼ���ṹ�����
	NVIC_InitTypeDef  NVIC_InitStructure;

	// ����һ����ʱ��ʱ���׼��ʼ���ṹ�����
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);


	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; // ����ʱ�ӷ�Ƶ����Ϊ1
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // ���ü���ģʽΪ���ϼ���
	TIM_TimeBaseInitStructure.TIM_Period = 1000-1; 
	TIM_TimeBaseInitStructure.TIM_Prescaler = 144-1; 
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

	// ����NVIC�жϿ������������Ա�TIM4��ʱ���жϿ��Ա���Ӧ
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; // �����ж�ͨ��ΪTIM4��ʱ���ж�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // ʹ�ܸ��ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // ������ռ���ȼ�Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; // ���������ȼ�Ϊ2

	// ʹ��ǰ�����õ�NVIC������ʼ��NVIC�жϿ�����
	NVIC_Init(&NVIC_InitStructure);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM2, ENABLE);
}

void TIMer6_Init(void)
{
	// ����һ��NVIC��ʼ���ṹ�����
	NVIC_InitTypeDef  NVIC_InitStructure;

	// ����һ����ʱ��ʱ���׼��ʼ���ṹ�����
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);


	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; // ����ʱ�ӷ�Ƶ����Ϊ1
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // ���ü���ģʽΪ���ϼ���
	TIM_TimeBaseInitStructure.TIM_Period = 1000-1; 
	TIM_TimeBaseInitStructure.TIM_Prescaler = 84-1; 
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStructure);
	
	// ����NVIC�жϿ������������Ա�TIM4��ʱ���жϿ��Ա���Ӧ
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn; // �����ж�ͨ��ΪTIM4��ʱ���ж�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // ʹ�ܸ��ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // ������ռ���ȼ�Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; // ���������ȼ�Ϊ2

	// ʹ��ǰ�����õ�NVIC������ʼ��NVIC�жϿ�����
	NVIC_Init(&NVIC_InitStructure);

	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM6, ENABLE);
}
