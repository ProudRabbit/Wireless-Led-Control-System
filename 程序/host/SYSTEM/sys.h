#ifndef _SYS_H_
#define _SYS_H_

#include "intrins.h"
#include "reg52.h"

//--定义数码管输出使用的IO口--//
#define GPIO_DIG  	 	P0			//段选
#define GPIO_PLACE 		P1			//位选

//--选择数码管使用的模式--//
#define DIG_PLACE_SELECT 		0	//0为使用阴极接法的位选码
#define DIG_DIG_CODE_SELECT 	0	//0为使用共阴极接法的段选码

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

