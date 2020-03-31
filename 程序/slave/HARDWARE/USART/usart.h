#ifndef _USART_H_
#define _USART_H_

#include "sys.h"

#define USART_SIZE 6		////串口数据缓存大小

extern unsigned char R_STA;
extern unsigned char res;
extern unsigned char str[USART_SIZE];

extern void UART_Init();
extern void UART_Putch(uchar idata *dat) ;


#endif
