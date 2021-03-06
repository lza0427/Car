#include <stm32f10x.h>
#include "control.h"
#include "encoder.h"
#include "motor.h"
#include "delay.h"

extern int Velocity, Angle;

int main(void){
	
	Encoder_Init_TIM2();
	Encoder_Init_TIM3();
	MiniBalance_PWM_Init(7200, 99);
	Servo_PWM_Init(7200,99);
	
	while(1){
		Angle = 200;
		Velocity = 1000;
		Delay_s(10);
		
		Angle = 500;
		Velocity = 200;
		Delay_s(10);
	}
}
