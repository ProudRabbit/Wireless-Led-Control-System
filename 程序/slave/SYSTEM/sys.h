#ifndef _SYS_H_
#define _SYS_H_

#include "intrins.h"
#include "reg52.h"

//---定义IIC接口---//
sbit IIC_SCL = P2^1;
sbit IIC_SDA = P2^0;

//---定义AT24C02器件地址---//
#define AT24C02_Write	0xA0
#define AT24C02_Read	0xA1

//---定义按键端口---//
sbit KEY0 = P2^4;
sbit KEY1 = P2^5;
sbit KEY2 = P2^6;
sbit KEY3 = P2^7;

typedef unsigned char uchar;
typedef unsigned int uint;

typedef unsigned char BYTE;
typedef unsigned int WORD;


#endif

