#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "led.h"

int ID = 0;				//设备ID

void main()
{
	UART_Init();
	
	while(1)
	{
		if(str[1]==0x01)
		{
			Led_ON();
		}
		else
		{
			Led_OFF();
		}
		R_STA = 0;		//处理数据后清除串口接收标志
		Delay5ms();
	}
}
