#include "sys.h"
#include "usart.h"
#include "delay.h"

void main()
{
	UART_Init();
	
	while(1)
	{
		
		Delay5ms();
	}
}
