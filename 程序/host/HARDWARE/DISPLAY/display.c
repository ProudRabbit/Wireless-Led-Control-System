#include "display.h"

//--����ȫ�ֱ���--//
unsigned char code DIG_PLACE[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};//λѡ����   ���ķ�������
unsigned char code DIG_CODE[17] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
									0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
									//0��1��2��3��4��5��6��7��8��9��A��b��C��d��E��F����ʾ�� �������ӷ�
unsigned char DisplayData[8]={0};	//�������Ҫ��ʾ��8λ����ֵ

/*******************************************************************************
* �� �� ��         : DigDisplay
* ��������		   : ʹ���������ʾ
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void DigDisplay()
{
	unsigned char i;
	unsigned int j;
	
	for(i=0; i<8; i++)
	{
		DisplayData[i] = DIG_CODE[i];
		GPIO_PLACE = DIG_PLACE[i];	 //����λѡ
		GPIO_DIG = DisplayData[i];     //���Ͷ���
		j = 10;						 //ɨ����ʱ���趨
		while(j--);	
		GPIO_DIG = 0x00;//����
	}
}