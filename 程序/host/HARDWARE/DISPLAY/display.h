#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "sys.h"


extern unsigned char code DIG_PLACE[8];		//位选控制   查表的方法控制
extern unsigned char code DIG_CODE[10];		//存放显示码 共阴极接法
extern unsigned char DisplayData[8];		//用来存放要显示的8位数的值ֵ

extern void DigDisplay(int m); 				//动态显示函数

#endif