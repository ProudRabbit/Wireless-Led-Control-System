#include "key.h"

int key = 0;

//mode == 1Ϊ֧����������0Ϊ��֧��,
//����ֵΪ��ֵ,0Ϊ�ް�������
int KEY_Scan(int mode)		
{
	static int KeyUp_flag = 1;
	if(mode == 1)
		KeyUp_flag = 1;
	
	if((KeyUp_flag == 1)&&(KEY0 == 0||KEY1 ==0||KEY2 == 0||KEY3 == 0))
	{
		delay_nms(10);	//����
		KeyUp_flag = 0;
		if(KEY0 == 0)return 1;
		else if(KEY1 == 0)return 2;
		else if(KEY2 == 0)return 3;
		else if(KEY3 == 0)return 4;
	}
	else if(KEY0 == 1&&KEY1 ==1&&KEY2 == 1&&KEY3 == 1)
		KeyUp_flag = 1;
	return 0;	//�ް�������
	
}