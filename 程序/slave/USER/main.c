#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "eeprom.h"

unsigned char ID = 0x03;					//设备ID
unsigned char comd1 = 0x00;					//全部点亮忽视ID
unsigned char comd2 = 0x00;					//根据ID点亮
uint Config_flag = 0;						//是否进入参数配置标志位 1位进入配置模式
uint index = 0;								//记录设置的是第几个参数

void main()
{
	BYTE tmp =0;
	int key = 0;
	
	UART_Init();
	
	if(AT24C02_Check()==0)
	{
		ID = ReadOneByte(0);				//存有数据，读出ID值
	}
	
	EA = 1;
	P0 = 0X00;
	
	while(1)
	{
		if(Config_flag==0)				//正常工作模式
		{
			if((R_STA&0x80)==0x80)
			{
				comd1 = str[1];
				comd2 = str[2];
				R_STA = 0;		//处理数据后清除串口接收标志
				//UART_Putch(str);
			}
			
			key = KEY_Scan(0);
			if(key == 1)							//切换配置模式
			{
				Config_flag = 1;
				EA = 0;
				P0 |= 0X80; 
			}
			
			if((comd1 == 0x01)||(comd2 == ID))
			{
				Led_ON();
			}
			else
			{
				Led_OFF();
			}
		}
		else
		{
			key = KEY_Scan(0);
			if(key == 1)				//退出配置模式
			{
				Config_flag = 0;
				EA = 1;
				P0 &= 0x7f;
			}
			else if(key == 2)
			{
				ID = 0x01;
				WriteOneByte(0,ID);					//更新ID
				WriteOneByte(255,0x55);				//更新标志位
				P0 |=0X04;
			}
			else if(key == 3)
			{
				ID = 0x02;
				WriteOneByte(0,ID);					//更新ID
				WriteOneByte(255,0x55);				//更新标志位
				P0 |=0X02;
			}
		}
	}
}
