#include "sys.h"


void main()
{
	UART_Init();	//��ʼ������
	TIM_Init();		//��ʼ����ʱ��
	
	while(1)
	{
		DigDisplay();		//��ʾʱ��
		key = KEY_Scan(1);	//֧��������
		UART_Putch(str);	//����һ���ֽ�
		Delay5ms();
	}
}
