#include "sys.h"


void main()
{
	UART_Init();	//初始化串口
	TIM_Init();		//初始化定时器
	
	while(1)
	{
		DigDisplay();		//显示时间
		key = KEY_Scan(1);	//支持连续按
		UART_Putch(str);	//发送一个字节
		Delay5ms();
	}
}
