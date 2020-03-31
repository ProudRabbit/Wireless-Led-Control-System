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



//void WriteVartoRom(BYTE* arr,uint SIZE);
//void ReadRomToVar(BYTE* arr,uint SIZE);
//void UpVarTmp(int mode);
//void ClearVarTmp(uint SIZE);

#endif
