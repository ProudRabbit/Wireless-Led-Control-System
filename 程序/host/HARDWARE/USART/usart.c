#include "usart.h"

unsigned char R_X = 0; 
unsigned char idata str[6] = {0x39,0x00,0x00,0x00,0x00,0x39};


void UART_Init() //��ʼ��uart
{  
	TMOD=0X20;  //��ʱ��1��ʱ����ʽ ����ģʽ2
	SCON=0X51; //ѡ����ģʽ1ʹ�ܽ��գ������ͣ��������	
	EA=1; //�����ж�	
	ES=1;  //�������ж�
	ET1=0;  //����ʱ���ж�	
	PCON=0X80; //8λ�Զ����أ������ʼӱ�	
	TH1=0XFA;  //��22.1184 mhz������
	TL1=0XFA; 
	TR1=1; //�򿪶�ʱ��1
}



void UART_Putch(uchar idata *dat)  //���һ���ֽ�
{
   uchar i;
   for(i=0 ;i<6;i++)	
   {
			SBUF=dat[i]; //�������͵�sbuf��������					  
			while(TI!=1);	//���ͱ�־λT1���������Ϊ1��û����Ϊ0��û���͵ȴ��������˳�ѭ��
			TI=0;  //����T1����
	}
}


void UART_IRQHandler() interrupt 4  //uart�ж� ,4Ϊ�����ж�
{
 
	  if(RI==1)  //�յ�����
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