#include "sys.h"  
#include "key.h" 

uint8_t main_mode = 1;
uint8_t number=0;
uint8_t pe2_pressed = 0;
uint8_t pe3_pressed = 0;
void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitTypeDefstruct;
	//ʹ��GPIOC��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	//��ʼ��IO��
	GPIO_InitTypeDefstruct.GPIO_Mode=GPIO_Mode_IN;

	GPIO_InitTypeDefstruct.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitTypeDefstruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitTypeDefstruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitTypeDefstruct);
	GPIO_InitTypeDefstruct.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_5;
	GPIO_InitTypeDefstruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitTypeDefstruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitTypeDefstruct);
	
}

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitTypeDefstruct;
	//ʹ��GPIOC��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOB,ENABLE);
	//��ʼ��IO��
	GPIO_InitTypeDefstruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitTypeDefstruct.GPIO_OType=GPIO_OType_PP;
	//PC2������
	GPIO_InitTypeDefstruct.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitTypeDefstruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitTypeDefstruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitTypeDefstruct);
	GPIO_SetBits(GPIOC,GPIO_Pin_2);
	
	GPIO_InitTypeDefstruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitTypeDefstruct.GPIO_OType=GPIO_OType_PP;
	//PB13 PB14
	GPIO_InitTypeDefstruct.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitTypeDefstruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitTypeDefstruct);
	
	
}
void TCRT5000_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_0;      // DO��PB0
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN;    // ����ģʽ �������ź�
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
}


void EXTIXa_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;// �����ж����ȼ��ṹ�����
	EXTI_InitTypeDef EXTI_InitStructure;//�����ⲿ�жϽṹ��ṹ�����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE); //ʹ��SYSCFGʱ��
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource2); //PE7�����ж���7��ӳ�䰴��KEY_UP   ����˵ �������������ʵ�ְ����Ž��ڶ�Ӧ���ж����ϣ������ڸ��ù���
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource3); //PE8�����ж���8��ӳ�䰴��KEY2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource4); //PE9�����ж���9��ӳ�䰴��KEY1
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource5); //PE10�����ж���10��ӳ�䰴��KEY0
	
	//����֮����Ҫ�ֿ�����EXTI��ʼ������������ΪKEY_UP�Ǹߵ�ƽ1��Ч��KEY0/KEY1/KEY2�ǵ͵�ƽ0��Ч��
	//���������غ��½�����Ҫ�ֿ�����
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line2| EXTI_Line3 | EXTI_Line4 | EXTI_Line5;//�ж���2/3/4
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;//�ж�ʹ��
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;//ģʽ�ж�
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//�½���  ԭ��ͼ��KEY0/KEY1/KEY2���ӵأ�����һ�����£���ʾ���ŵ͵�ƽ��Ҳ�����½�����Ч
	EXTI_Init(&EXTI_InitStructure);//��ʼ���ⲿ�ж�
	
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI2_IRQn;//�ⲿ�ж�0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//ʹ���ⲿ�ж�0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x02;//��Ӧ���ȼ�2
	NVIC_Init(&NVIC_InitStructure);//��ʼ���ж����ȼ�
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI3_IRQn;//�ⲿ�ж�2
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//ʹ���ⲿ�ж�2
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x03;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x02;//��Ӧ���ȼ�2
	NVIC_Init(&NVIC_InitStructure);//��ʼ���ж����ȼ�
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI4_IRQn;//�ⲿ�ж�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//ʹ���ⲿ�ж�3
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02;//��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x02;//��Ӧ���ȼ�2
	NVIC_Init(&NVIC_InitStructure);//��ʼ���ж����ȼ�
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;//�ⲿ�ж�4
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//ʹ���ⲿ�ж�4
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01;//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x02;//��Ӧ���ȼ�2
	NVIC_Init(&NVIC_InitStructure);//��ʼ���ж����ȼ�
}



void EXTI2_IRQHandler(void)  //�ⲿ�ж���0�жϷ�����
{
	
 	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0 && pe2_pressed == 0)
	{
	  pe2_pressed = 1;
	  delay_ms(20);
	  while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0);
	  delay_ms(20);
	  number++;
	  if(number>=13)number=0;
	}
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1)
	{
	  pe2_pressed = 0;
	}
	 EXTI_ClearITPendingBit(EXTI_Line2); //���LINE0�ϵ��жϱ�־λ 
}
void EXTI3_IRQHandler(void)//�ж���2���ⲿ�жϷ�����
{
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0 && pe3_pressed == 0)
	{
	  pe3_pressed = 1;
	  delay_ms(20);
	  while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0);
	  delay_ms(20);
	  main_mode=number;
	}
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1)
	{
	  pe3_pressed = 0;
	}
	EXTI_ClearITPendingBit(EXTI_Line3);//�����ж���2�ϵ��жϱ�־λ
}
void EXTI4_IRQHandler(void)//�ж���3���ⲿ�жϷ�����
{
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)==0)
	{
	    delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)==0);
		delay_ms(20);
		main_mode=13;
	}
	EXTI_ClearITPendingBit(EXTI_Line4);//�����ж���3�ϵ��жϱ�־λ
}
void EXTI9_5_IRQHandler (void)//�ж���4���ⲿ�жϷ�����
{
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0)
	{
	    delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0);
		delay_ms(20);
	}
	EXTI_ClearITPendingBit(EXTI9_5_IRQn);//�����ж���4�ϵ��жϱ�־λ
}
