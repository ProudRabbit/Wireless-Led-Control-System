#ifndef _SYS_H_
#define _SYS_H_

#include "intrins.h"
#include "reg52.h"

//---定义数码管的接法---//
#define DIG_PLACE_SELECT 	0			//0为阴极接法 1为阳极接法
#define DIG_CODE_SELECT 	0			//0为阴极接法 1为阳极接法

//---定义数码管使用的IO口---//
#define GPIO_PLACE			P1
#define GPIO_DIG			P0

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

