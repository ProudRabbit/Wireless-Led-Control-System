#ifndef _KEY_H_
#define _KEY_H_

#include "key.h"
#include "sys.h"

//���尴���˿�
sbit KEY0 = P1^0;
sbit KEY1 = P1^1;
sbit KEY2 = P1^2;
sbit KEY3 = P1^3;


extern int key;	//��ż�ֵ

//mode == 1Ϊ֧����������0Ϊ��֧��,
//����ֵΪ��ֵ,0Ϊ�ް�������
extern int KEY_Scan(int mode);	


#endif