#include "sys.h"
#include "delay.h"
#include "display.h"
#include "usart.h"
#include "tim.h"
#include "key.h"
#include "eeprom.h"

#define ODD_LED_LIGHT 	0X01	//奇数点亮 使用str[2]
#define EVEN_LED_LIGHT 	0X02	//偶数点亮 使用str[2]
#define ALL_LED_LIGHT 	0X01	//全点亮使能命令 放在str[1]中

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
			flag_1s = 0;
			time--;
		}
		switch(time)
		{
			case 30:					//奇数点亮
				str[1]=0x00;
				str[2]=ODD_LED_LIGHT;
				break;
			case 20:					//偶数点亮
				str[1]=0x00;
				str[2]=EVEN_LED_LIGHT;
				break;
			case 10:					//全亮
				str[1]=ALL_LED_LIGHT;
				break;
			default:
				break;
		}

		DigDisplay(time);
		
		key = KEY_Scan(0);	//不支持连续按 0不支持 1支持
		if(key == 1)
		{
			IapProgramByte(IAP_ADDRESS,(BYTE)6);
		}	
		else if(key == 2)
		{
			UART_Putch(str);
			R_STA = 0;			//处理完缓存区数据，重新开始接收
		}
		else if(key == 3)
		{
			str[1]=IapReadByte(IAP_ADDRESS);	//读取一个字节
		}
		
		UART_Putch(str);			//下发控制命令
		Delay5ms();
	}
}
