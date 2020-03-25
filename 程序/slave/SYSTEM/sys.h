#ifndef _SYS_H_
#define _SYS_H_

#include "intrins.h"
#include "reg52.h"

//---定义按键端口---//
sbit KEY0 = P2^0;
sbit KEY1 = P2^1;
sbit KEY2 = P2^2;
sbit KEY3 = P2^3;

typedef unsigned char uchar;
typedef unsigned int uint;

typedef unsigned char BYTE;
typedef unsigned int WORD;


#endif

