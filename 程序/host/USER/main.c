#include "sys.h"
#include "delay.h"
#include "display.h"
#include "usart.h"
#include "tim.h"
#include "key.h"
#include "eeprom.h"

uint i = 0;


void main()
{
	UART_Init();	//初始化串口
	TIM_Init();		//初始化定时器

    //IapEraseSector(IAP_ADDRESS);    //Erase current sector

	//Delay5ms();
	
	//IapProgramByte(IAP_ADDRESS,(BYTE)6);
	//Delay5ms();
	
	while(1)
	{
		if(flag_1s == 1)
		{
			if(time == 0)
				time = 30;
			time--;
		}
		
		DigDisplay(30);
		
		key = KEY_Scan(0);	//不支持连续按 0不支持 1支持
		if(key == 1)
			i = IapReadByte(IAP_ADDRESS);	//读取一个字节
		else if(key == 2)
		{
			str[1] = i;
			UART_Putch(str);
		}
		Delay5ms();
	}
}
