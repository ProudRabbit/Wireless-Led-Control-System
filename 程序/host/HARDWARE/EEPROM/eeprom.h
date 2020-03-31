#ifndef _EEPROM_H_
#define _EEPROM_H_

#include "sys.h"
#include "delay.h"

extern void IIC_Start(void);
extern void IIC_Stop(void);
extern BYTE IIC_WaitAck(void);
extern void IIC_Ack(void);
extern void IIC_nAck(void);
extern void IIC_Send_Byte(BYTE dat);
extern BYTE IIC_Read_Byte(BYTE ack);
extern void WriteOneByte(uint addr,BYTE dat);
extern BYTE ReadOneByte(uint addr);
extern uint AT24C02_Check(void);


extern uint time_com1;
extern uint time_com2;
extern uint time_com3;
extern uint time_backup;
extern BYTE var_tmp[4];




extern void WriteVartoRom(uint addr,BYTE* arr,uint SIZE);
extern void ReadRomToVar(uint addr,BYTE* arr,uint SIZE);
extern void UpVarTmp(int mode);
extern void ClearVarTmp(uint SIZE);

#endif
