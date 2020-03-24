#include "display.h"
#include "delay.h"

unsigned char code DIG_PLACE[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};	//位选控制

unsigned char code DIG_CODE[17] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
									0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
									//0 1 2 3 4 5 6 7 8 9 A B C D E F 的段码 共阴极接法
									
unsigned char DisplayData[8]={0};	//存放要显示的段码

/*******************************************************************************
* 函数名         : DigDisplay
* 功能		  	 : 数码管动态显示
* 输入			 ：时间0 - 60秒
* 输出			 : 无
*******************************************************************************/

void DigDisplay(int m)
{
	unsigned char i;
	unsigned char j;
	
	DisplayData[7] = DIG_CODE[m%10];		//得到个位段码
	DisplayData[6] = DIG_CODE[m/10];		//得到十位段码

	for(i=0; i<8; i++)
	{
		
		GPIO_PLACE = DIG_PLACE[i];	 	//输出位选
		GPIO_DIG = DisplayData[i];     	//输出段码
		
		j = 40;
		while(j--);
		GPIO_DIG = 0x00;			//消隐
	}
}