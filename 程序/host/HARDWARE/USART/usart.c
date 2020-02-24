#include "usart.h"

unsigned char R_X = 0; 
unsigned char idata str[6] = {0x39,0x00,0x00,0x00,0x00,0x39};


void UART_Init() //初始化uart
{  
	TMOD=0X20;  //定时器1定时器方式 工作模式2
	SCON=0X51; //选择工作模式1使能接收，允许发送，允许接收	
	EA=1; //开总中断	
	ES=1;  //开串口中断
	ET1=0;  //开定时器中断	
	PCON=0X80; //8位自动重载，波特率加倍	
	TH1=0XFA;  //用22.1184 mhz波特率
	TL1=0XFA; 
	TR1=1; //打开定时器1
}



void UART_Putch(uchar idata *dat)  //输出一个字节
{
   uchar i;
   for(i=0 ;i<6;i++)	
   {
			SBUF=dat[i]; //把数据送到sbuf缓冲器中					  
			while(TI!=1);	//发送标志位T1如果发送了为1，没发送为0，没发送等待，到了退出循环
			TI=0;  //到了T1清零
	}
}


void UART_IRQHandler() interrupt 4  //uart中断 ,4为串口中断
{
 
	  if(RI==1)  //收到数据
	  {
			R_X=SBUF;
			if(R_X==0x23)
			{  
				UART_Putch(str);
				RI=0;
			}
			else
			{
				RI=0;
			}
	  }
}