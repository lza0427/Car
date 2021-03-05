#include "led_key.h"

int ledFlag = 0;

void Led_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void Key_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure; 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
		
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line0; 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetFlagStatus(EXTI_Line0) == SET)
	{
		ledFlag = ~ledFlag;
		GPIO_WriteBit(GPIOA, GPIO_Pin_1, ledFlag);
		EXTI_ClearFlag(EXTI_Line0);
	}
	
}
