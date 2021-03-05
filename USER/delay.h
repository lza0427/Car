#ifndef __DELAY_H
#define __DELAY_H


#ifdef __cplusplus
extern "C" {
#endif

/* Header includes -----------------------------------------------------------*/
#include <stm32f10x.h>

/* Macro definitions ---------------------------------------------------------*/
/* Type definitions ----------------------------------------------------------*/
/* Variable declarations -----------------------------------------------------*/
/* Variable definitions ------------------------------------------------------*/
/* Function declarations -----------------------------------------------------*/
void Delay_us(uint64_t nus);
void Delay_ms(uint64_t nms);
void Delay_s(uint64_t ns);

/* Function definitions ------------------------------------------------------*/

#ifdef __cplusplus
}
#endif




#endif
