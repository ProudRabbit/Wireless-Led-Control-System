#ifndef _LED_H_
#define _LED_H_

#include "sys.h"

//--定义LED使用的端口--//
sbit led = P0^4;		//阳极接法

void Led_ON(void);
void Led_OFF(void);

#endif
