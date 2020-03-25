#ifndef _KEY_H_
#define _KEY_H_

#include "key.h"
#include "sys.h"




extern int key;	//存放键值

//mode == 1为支持连续按，0为不支持,
//返回值为键值,0为无按键按下
extern int KEY_Scan(int mode);	


#endif