#include "tim.h"


unsigned int t = 0;

void TIM_Init()
{
	TMOD |= 0X01;		//定时器0工作方式1
	TH0 = (65536-50000)/256;		//定时50毫秒
	TL0 = (65536-50000)%256;
	ET0 = 1;			//开定时器0中断
	TR0 = 1;			//启动定时器0
}



void TIM_IRQHandler() interrupt 1
{
	TH0 = (65536-50000)/256;
	TL0 = (65536-50000)%256;
	t++;
}