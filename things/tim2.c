#include "tim2.h"

int times = 0;

void Tim2_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = 999; 
	TIM_TimeBaseStructure.TIM_Prescaler = 71; 
	//TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, DISABLE);

}

void TIM2_IRQHandler(void)
{
//		if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET){
//		
//		times++;
//		if(times == 100)
//		{
//		ledFlag2 = ~ledFlag2;
//		GPIO_WriteBit(GPIOA, GPIO_Pin_1, ledFlag2);
//		times = 0;
//		}
//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//	}

		times --;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}
	
void delay(unsigned long n){
	TIM_Cmd(TIM2, ENABLE);
	times = n;
	while(times);
	TIM_Cmd(TIM2, DISABLE);
}
