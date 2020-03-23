#ifndef _TIM_H_
#define _TIM_H_

#include "sys.h"

extern unsigned int t;			//定时中断计数
extern uint flag_1s;			//定时1秒标志位
extern int time;				//30秒倒计时
extern void TIM_Init();			//定时器0初始化



#endif