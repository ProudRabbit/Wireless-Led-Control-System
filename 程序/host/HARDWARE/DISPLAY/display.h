#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "sys.h"

//--����ʹ�õ�IO��--//
#define GPIO_DIG   P0	//��ѡ
#define GPIO_PLACE P1	//λѡ

extern unsigned char code DIG_PLACE[8];	//ѡ����   ���ķ�������
extern unsigned char code DIG_CODE[17];	//�����ʾ�� �������ӷ�
extern unsigned char DisplayData[8];	//�������Ҫ��ʾ��8λ����ֵ

extern void DigDisplay(); //��̬��ʾ����

#endif