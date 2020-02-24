#include "tim.h"


unsigned int t = 0;

void TIM_Init()
{
	TMOD |= 0X01;		//��ʱ��0������ʽ1
	TH0 = (65536-50000)/256;		//��ʱ50����
	TL0 = (65536-50000)%256;
	ET0 = 1;			//����ʱ��0�ж�
	TR0 = 1;			//������ʱ��0
}



void TIM_IRQHandler() interrupt 1
{
	TH0 = (65536-50000)/256;
	TL0 = (65536-50000)%256;
	t++;
}