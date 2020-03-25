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

uint time_com1=30;
uint time_com2=20;
uint time_com3=10;
BYTE var_tmp[4] ={0x00,0x00,0x00,0x00};		//缓存四个时间：时间，发送指令1的时间，发送指令2的时间，发送指令3的时间

uint Config_flag = 0;						//是否进入参数配置标志位 1位进入配置模式
uint index = 0;								//记录设置的是第几个参数

void main()
{
	BYTE tmp =0;
	
	UART_Init();	//初始化串口
	TIM_Init();		//初始化定时器
	
	
	tmp=IapReadByte(IAP_ADDRESS);
	if((tmp==0x00)||(tmp==0xff))				//重新下载程序了，需要重新写入数据到ROM
	{
		UpVarTmp(1);							//更新var_tmp
		WriteVartoRom(var_tmp,sizeof(var_tmp));
		ClearVarTmp(sizeof(var_tmp));
	}
	else
	{
		ReadRomToVar(var_tmp,sizeof(var_tmp));
		UpVarTmp(0);							//更新var_tmp到Date
		ClearVarTmp(sizeof(var_tmp));
	}
	
	
	EA = 1;				//开总中断
	
	while(1)
	{
		
		if(Config_flag==0)				//正常工作模式
		{
			if(flag_1s == 1)
			{
				if(time == 0)
					time = time_backup;
				flag_1s = 0;
				time--;
			}
			if(time==time_com1)						//奇数点亮
			{				
				str[1]=0x00;
				str[2]=ODD_LED_LIGHT;
			}
			else if(time==time_com2)				//偶数点亮
			{
				str[1]=0x00;
				str[2]=EVEN_LED_LIGHT;
			}
			else if(time==time_com3)				//全亮
			{
				str[1]=ALL_LED_LIGHT;
			}

			DigDisplay(time);						//数码管显示
			
			key = KEY_Scan(0);						//不支持连续按 0不支持 1支持
			if(key == 1)							//切换配置模式
			{
				Config_flag = 1;
				EA = 0;
			}
			
			UART_Putch(str);						//下发控制命令
		}
		else
		{
			key = KEY_Scan(0);
			if(key == 1)				//退出配置模式
			{
				Config_flag = 0;
				EA = 1;
			}
			else if(key == 4)
			{
				index++;
			}
			
			switch(index)
			{
				case 0:								//配置时间
					key = KEY_Scan(1);
					if(key == 2) time_backup++;
					else if(key == 3) time_backup--;
					DigDisplay(time_backup);
					break;
				case 1:								//配置下发指令1的时间
					key = KEY_Scan(1);
					if(key == 2) time_com1++;
					else if(key == 3) time_com1--;
					DigDisplay(time_com1);
					break;
				case 2:								//配置下发指令2的时间
					key = KEY_Scan(1);
					if(key == 2) time_com2++;
					else if(key == 3) time_com2--;
					DigDisplay(time_com2);
					break;
				case 3:								//配置下发指令3的时间
					key = KEY_Scan(1);
					if(key == 2) time_com3++;
					else if(key == 3) time_com3--;
					DigDisplay(time_com3);
					break;
				default:							//写入数据到ROM
					UpVarTmp(1);
					WriteVartoRom(var_tmp,sizeof(var_tmp));
					UpVarTmp(0);
					ClearVarTmp(sizeof(var_tmp));
					Config_flag = 0;
					index = 0;
					EA = 1;
					break;
			}
		}
		Delay5ms();
	}
}
