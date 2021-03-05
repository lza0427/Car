#include "delay.h"
#include <stm32f10x.h>

//void Tim7configure(){
//	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM7 , ENABLE);
//	
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure; 
//	TIM_TimeBaseInitStructure.TIM_Period = 72;
//	TIM_TimeBaseInitStructure.TIM_Prescaler = 999;
//	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Down;
//	TIM_TimeBaseStructInit(& TIM_TimeBaseInitStructure);
//	
//	
//} 


void Delay_us(uint64_t nus)
{
  uint64_t nms = 0;
  
  if(nus == 0)
  {
    return;
  }
  
  nms = nus / 1000;
  nus = nus % 1000;
  
  if(nms > 0)
  {
    Delay_ms(nms);
  }
  
  if(nus > 0)
  {
    RCC_ClocksTypeDef RCC_ClockFreq;
    
    RCC_GetClocksFreq(&RCC_ClockFreq);                              /* Get the frequencies of different on chip clocks. */
    
    if(RCC_ClockFreq.HCLK_Frequency < 8000000)
    {
      SysTick->CTRL |= SysTick_CLKSource_HCLK;                      /* Configures the SysTick clock source. */
      SysTick->LOAD = RCC_ClockFreq.HCLK_Frequency / 1000000 * nus; /* Time load (SysTick-> LOAD is 24bit). */
    }
    else
    {
      SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;                 /* Configures the SysTick clock source. */
      SysTick->LOAD = RCC_ClockFreq.HCLK_Frequency / 8000000 * nus; /* Time load (SysTick-> LOAD is 24bit). */
    }
    
    SysTick->VAL = 0;                                               /* Empty counter. */
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;                       /* Start the countdown. */
    
    while((SysTick->CTRL&(1UL<<16)) != (1UL<<16));                  /* Wait time is reached. */
    
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;                      /* Close counter. */
  }
}


void Delay_ms(uint64_t nms)
{
	RCC_ClocksTypeDef RCC_ClockFreq;
	
  if(nms == 0)
  {
    return;
  }
  
  while(nms > 500)
  {
    RCC_ClocksTypeDef RCC_ClockFreq;
    
    RCC_GetClocksFreq(&RCC_ClockFreq);                            /* Get the frequencies of different on chip clocks. */
    
    if(RCC_ClockFreq.HCLK_Frequency < 8000000)
    {
      SysTick->CTRL |= SysTick_CLKSource_HCLK;                    /* Configures the SysTick clock source. */
      SysTick->LOAD = RCC_ClockFreq.HCLK_Frequency / 1000 * 500;  /* Time load (SysTick-> LOAD is 24bit). */
    }
    else
    {
      SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;               /* Configures the SysTick clock source. */
      SysTick->LOAD = RCC_ClockFreq.HCLK_Frequency / 8000 * 500;  /* Time load (SysTick-> LOAD is 24bit). */
    }
    
    SysTick->VAL = 0;                                             /* Empty counter. */
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;                     /* Start the countdown. */
    
    while((SysTick->CTRL&(1UL<<16)) != (1UL<<16));                /* Wait time is reached. */
    
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;                    /* Close counter. */
    
    nms -= 500;
  }
  
  
  
  RCC_GetClocksFreq(&RCC_ClockFreq);                              /* Get the frequencies of different on chip clocks. */
  
  if(RCC_ClockFreq.HCLK_Frequency < 8000000)
  {
    SysTick->CTRL |= SysTick_CLKSource_HCLK;                      /* Configures the SysTick clock source. */
    SysTick->LOAD = RCC_ClockFreq.HCLK_Frequency / 1000 * nms;    /* Time load (SysTick-> LOAD is 24bit). */
  }
  else
  {
    SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;                 /* Configures the SysTick clock source. */
    SysTick->LOAD = RCC_ClockFreq.HCLK_Frequency / 8000 * nms;    /* Time load (SysTick-> LOAD is 24bit). */
  }
  
  SysTick->VAL = 0;                                               /* Empty counter. */
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;                       /* Start the countdown. */
  
  while((SysTick->CTRL&(1UL<<16)) != (1UL<<16));                  /* Wait time is reached. */
  
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;                      /* Close counter. */
}




void Delay_s(uint64_t ns)
{
  while(ns > 0)
  {
    Delay_ms(1000);
    ns--;
  }
}