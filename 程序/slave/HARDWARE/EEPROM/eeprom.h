#ifndef _EEPROM_H_
#define _EEPROM_H_

#include "sys.h"
//#include "tim.h"

/*Declare SFR associated with the IAP */
sfr IAP_DATA    =   0xE2;           //Flash data register
sfr IAP_ADDRH   =   0xE3;           //Flash address HIGH
sfr IAP_ADDRL   =   0xE4;           //Flash address LOW
sfr IAP_CMD     =   0xE5;           //Flash command register
sfr IAP_TRIG    =   0xE6;           //Flash command trigger
sfr IAP_CONTR   =   0xE7;           //Flash control register

/*Define ISP/IAP/EEPROM command*/
#define CMD_IDLE    0               //Stand-By
#define CMD_READ    1               //Byte-Read
#define CMD_PROGRAM 2               //Byte-Program
#define CMD_ERASE   3               //Sector-Erase

/*Define ISP/IAP/EEPROM operation const for IAP_CONTR*/
//#define ENABLE_IAP 0x80           //if SYSCLK<40MHz
#define ENABLE_IAP   0x81           //if SYSCLK<20MHz
//#define ENABLE_IAP x82            //if SYSCLK<10MHz
//#define ENABLE_IAP 0x83           //if SYSCLK<5MHz

//Start address for STC89C58xx EEPROM
#define IAP_ADDRESS 0x08000

extern BYTE var_tmp[4];
extern uint time_com1;
extern uint time_com2;
extern uint time_com3;

//void Delay(BYTE n);
void IapIdle();
BYTE IapReadByte(WORD addr);
void IapProgramByte(WORD addr, BYTE dat);
//void IapEraseSector(WORD addr);


//void WriteVartoRom(BYTE* arr,uint SIZE);
//void ReadRomToVar(BYTE* arr,uint SIZE);
//void UpVarTmp(int mode);
//void ClearVarTmp(uint SIZE);

#endif
