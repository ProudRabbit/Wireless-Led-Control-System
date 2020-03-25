/*------------------------------------------------------------------*/
/* --- STC MCU Limited ---------------------------------------------*/
/* --- STC89-90xx Series MCU ISP/IAP/EEPROM Demo -------------------*/
/* --- Mobile: (86)13922805190 -------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ---------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966----------------------*/
/* --- Web: www.STCMCU.com -----------------------------------------*/
/* --- Web: www.GXWMCU.com -----------------------------------------*/
/* If you want to use the program or the program referenced in the  */
/* article, please specify in which data and procedures from STC    */
/*------------------------------------------------------------------*/

//#include "reg51.h"
//#include "intrins.h"

#include "eeprom.h"



/*----------------------------
Software delay function
----------------------------*/
//void Delay(BYTE n)
//{
//    WORD x;

//    while (n--)
//    {
//        x = 0;
//        while (++x);
//    }
//}

/*----------------------------
Disable ISP/IAP/EEPROM function
Make MCU in a safe state
----------------------------*/
void IapIdle()
{
    IAP_CONTR = 0;                  //Close IAP function
    IAP_CMD = 0;                    //Clear command to standby
    IAP_TRIG = 0;                   //Clear trigger register
    IAP_ADDRH = 0x80;               //Data ptr point to non-EEPROM area
    IAP_ADDRL = 0;                  //Clear IAP address to prevent misuse
}

/*----------------------------
Read one byte from ISP/IAP/EEPROM area
Input: addr (ISP/IAP/EEPROM address)
Output:Flash data
----------------------------*/
BYTE IapReadByte(WORD addr)
{
    BYTE dat;                       //Data buffer

    IAP_CONTR = ENABLE_IAP;         //Open IAP function, and set wait time
    IAP_CMD = CMD_READ;             //Set ISP/IAP/EEPROM READ command
    IAP_ADDRL = addr;               //Set ISP/IAP/EEPROM address low
    IAP_ADDRH = addr >> 8;          //Set ISP/IAP/EEPROM address high
    IAP_TRIG = 0x46;                //Send trigger command1 (0x46)
    IAP_TRIG = 0xb9;                //Send trigger command2 (0xb9)
    _nop_();                        //MCU will hold here until ISP/IAP/EEPROM operation complete
    dat = IAP_DATA;                 //Read ISP/IAP/EEPROM data
    IapIdle();                      //Close ISP/IAP/EEPROM function

    return dat;                     //Return Flash data
}

/*----------------------------
Program one byte to ISP/IAP/EEPROM area
Input: addr (ISP/IAP/EEPROM address)
       dat (ISP/IAP/EEPROM data)
Output:-
----------------------------*/
void IapProgramByte(WORD addr, BYTE dat)
{
    IAP_CONTR = ENABLE_IAP;         //Open IAP function, and set wait time
    IAP_CMD = CMD_PROGRAM;          //Set ISP/IAP/EEPROM PROGRAM command
    IAP_ADDRL = addr;               //Set ISP/IAP/EEPROM address low
    IAP_ADDRH = addr >> 8;          //Set ISP/IAP/EEPROM address high
    IAP_DATA = dat;                 //Write ISP/IAP/EEPROM data
    IAP_TRIG = 0x46;                //Send trigger command1 (0x46)
    IAP_TRIG = 0xb9;                //Send trigger command2 (0xb9)
    _nop_();                        //MCU will hold here until ISP/IAP/EEPROM operation complete
    IapIdle();
}

/*----------------------------
Erase one sector area
Input: addr (ISP/IAP/EEPROM address)
Output:-
----------------------------*/
//void IapEraseSector(WORD addr)
//{
//    IAP_CONTR = ENABLE_IAP;         //Open IAP function, and set wait time
//    IAP_CMD = CMD_ERASE;            //Set ISP/IAP/EEPROM ERASE command
//    IAP_ADDRL = addr;               //Set ISP/IAP/EEPROM address low
//    IAP_ADDRH = addr >> 8;          //Set ISP/IAP/EEPROM address high
//    IAP_TRIG = 0x46;                //Send trigger command1 (0x46)
//    IAP_TRIG = 0xb9;                //Send trigger command2 (0xb9)
//    _nop_();                        //MCU will hold here until ISP/IAP/EEPROM operation complete
//    IapIdle();
//}


/*******************************************************************************
* 函数名         : WriteVartoRom
* 功能		  	 : 写入var_tmp中数据到ROM
* 输入			 ：要写入的数组的地址和大小
* 输出			 : 无
*******************************************************************************/
void WriteVartoRom(BYTE* arr,uint SIZE)
{
	int i;
	for(i=0;i<SIZE;i++)
	{
		IapProgramByte(IAP_ADDRESS+i, (BYTE)arr[i]);
	}
}

/*******************************************************************************
* 函数名         : ReadRomToVar
* 功能		  	 : 读取ROM中数据到var_tmp
* 输入			 ：要读取到的数组的地址和大小
* 输出			 : 无
*******************************************************************************/
void ReadRomToVar(BYTE* arr,uint SIZE)
{
	int i;
	for(i=0;i<SIZE;i++)
	{
		arr[i]=IapReadByte(IAP_ADDRESS+i);
	}
}

/*******************************************************************************
* 函数名         : UpVarTmp
* 功能		  	 : 更新var_tmp缓存数组
* 输入			 ：mode 1 Date to var_tmp  0 var_tmp to Date
* 输出			 : 无
*******************************************************************************/
void UpVarTmp(int mode)
{
	if(mode==1)				//更新数据到var_tmp数组中
	{
		var_tmp[0]=time_backup;
		var_tmp[1]=time_com1;
		var_tmp[2]=time_com2;
		var_tmp[3]=time_com3;
	}
	else						//更新var_tmp数组中的数据到变量中
	{
		time_backup=var_tmp[0];
		time_com1=var_tmp[1];
		time_com2=var_tmp[2];
		time_com3=var_tmp[3];
	}
}

/*******************************************************************************
* 函数名         : ClearVarTmp
* 功能		  	 : 清空var_tmp缓存数组
* 输入			 ：var_tmp数组大小
* 输出			 : 无
*******************************************************************************/
void ClearVarTmp(uint SIZE)
{
	int i;
	for(i=0;i<SIZE;i++)
	{
		var_tmp[i]=0;
	}
}