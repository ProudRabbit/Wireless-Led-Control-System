#ifndef _USART_H_
#define _USART_H_

#include "sys.h"


extern unsigned char R_X;
extern unsigned char idata str[6];

extern void UART_Init();
extern void UART_Putch(unsigned char idata *dat);


#endif
