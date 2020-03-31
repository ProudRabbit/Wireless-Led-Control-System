/************************************************************
*
*			使用的芯片为AT24C02
*			 器件写入地址0xA0
*			 器件读取地址0xA1
*
************************************************************/

#include "eeprom.h"
#include "usart.h"

/*******************************************************************************
* 函数名   		: IIC_Start
* 功能			: IIC启动信号
* 输入			: 无
* 输出			: 无
*******************************************************************************/
void IIC_Start(void)
{
	IIC_SDA = 1;
	IIC_SCL = 1;
	Delay_4us();
	IIC_SDA = 0;
	Delay_4us();
	IIC_SCL = 0;
}

/*******************************************************************************
* 函数名   		: IIC_Stop
* 功能			: IIC停止信号
* 输入			: 无
* 输出			: 无
*******************************************************************************/
void IIC_Stop(void)
{
	IIC_SCL = 0;
	IIC_SDA = 0;
	Delay_4us();
	IIC_SCL = 1;
	Delay_4us();
	IIC_SDA = 1;
}

/*******************************************************************************
* 函数名   		: IIC_WaitAck
* 功能			: 等待Ack应答
* 输入			: 无
* 输出			: BYTE 1接收应答失败 0接收应答成功
*******************************************************************************/
BYTE IIC_WaitAck(void)
{
	BYTE errtime = 0;
	IIC_SDA = 1;
	_nop_();
	IIC_SCL = 1;
	_nop_();

	while (IIC_SDA)
	{
		errtime++;
		if(errtime>250)
		{		
			IIC_Stop();
			return 1;
		}
	}

	IIC_SCL = 0;
	return 0;
}

/*******************************************************************************
* 函数名   		: IIC_Ack
* 功能			: 产生Ack应答
* 输入			: 无
* 输出			: 无
*******************************************************************************/
void IIC_Ack(void)
{
	IIC_SCL = 0;
	Delay_4us();
	IIC_SDA = 0;
	Delay_4us();
	IIC_SCL = 1;
	Delay_4us();
	IIC_SCL = 0;
}

/*******************************************************************************
* 函数名   		: IIC_nAck
* 功能			: 不产生Ack应答
* 输入			: 无
* 输出			: 无
*******************************************************************************/
void IIC_nAck(void)
{
	IIC_SCL = 0;
	Delay_4us();
	IIC_SDA = 1;
	Delay_4us();
	IIC_SCL = 1;
	Delay_4us();
	IIC_SCL = 0;
}


/*******************************************************************************
* 函数名   		: IIC_Send_Byte
* 功能			: 发送一个字节
* 输入			: BYTE dat
* 输出			: 无
*******************************************************************************/
void IIC_Send_Byte(BYTE dat)
{
	BYTE t = 0;
	IIC_SCL = 0;
	for(t=0;t<8;t++)
	{
		IIC_SDA = ((dat&0x80)>>7);
		dat <<= 1;
		_nop_();
		IIC_SCL = 1;
		Delay_4us();
		IIC_SCL = 0;
	}
}

/*******************************************************************************
* 函数名   		: IIC_Read_Byte
* 功能			: 读取一个字节
* 输入			: BYTE ack 1为发送ACK 0为发送nACK
* 输出			: BYTE
*******************************************************************************/
BYTE IIC_Read_Byte(BYTE ack)
{
	BYTE i,receive = 0;
	for(i=0;i<8;i++)
	{
		IIC_SCL = 0;
		Delay_4us();
		IIC_SCL = 1;
		receive <<= 1;
		if(IIC_SDA==1)
		{
			receive++;
		}
		Delay_4us();
	}
	if(ack)
	{
		IIC_Ack();
	}
	else
	{
		IIC_nAck();
	}
	return receive;
}

/*******************************************************************************
* 函数名   		: WriteOneByte
* 功能			: 在24c02的地址为addr写入dat
* 输入			: 地址addr,数据dat
* 输出			: 
*******************************************************************************/
void WriteOneByte(uint addr,BYTE dat)
{
	IIC_Start();
	IIC_Send_Byte(AT24C02_Write);
	IIC_WaitAck();
	IIC_Send_Byte(addr);
	IIC_WaitAck();
	IIC_Send_Byte(dat);
	IIC_WaitAck();
	IIC_Stop();
	Delay_nms(20);
}

/*******************************************************************************
* 函数名   		: ReadOneByte
* 功能			: 读取24c02的地址为addr中的数据
* 输入			: 地址addr
* 输出			: data
*******************************************************************************/
BYTE ReadOneByte(uint addr)
{
	BYTE temp;
	IIC_Start();
	IIC_Send_Byte(AT24C02_Write);
	IIC_WaitAck();
	IIC_Send_Byte(addr);
	IIC_WaitAck();
	IIC_Start();
	IIC_Send_Byte(AT24C02_Read);
	IIC_WaitAck();
	temp = IIC_Read_Byte(0);
	IIC_Stop();
	return temp;
}

/*******************************************************************************
* 函数名   		: AT24C02_Check
* 功能			: 检查24C02是否存有数据
* 输入			: 
* 输出			: 0 存有数据，1不存有数据
*******************************************************************************/
uint AT24C02_Check(void)
{
	BYTE temp;
	temp=ReadOneByte(255);	   
	if(temp==0X55)
		return 0;		   
	else
		return 1;											  
}

/*******************************************************************************
* 函数名   		: WriteVartoRom
* 功能			: 写入var_tmp中数据到ROM
* 输入			: ROM中的地址和要写入的数组的地址和大小
* 输出			: 无
*******************************************************************************/
void WriteVartoRom(uint addr,BYTE* arr,uint SIZE)
{
	int i;
	for(i=0;i<SIZE;i++)
	{
		WriteOneByte((addr+i),arr[i]);
	}
}

/*******************************************************************************
* 函数名   		: ReadRomToVar
* 功能			: 读取ROM中数据到var_tmp
* 输入			: 要读取ROM中地址，缓存数组的地址和大小
* 输出			: 无
*******************************************************************************/
void ReadRomToVar(uint addr,BYTE* arr,uint SIZE)
{
	int i;
	for(i=0;i<SIZE;i++)
	{
		arr[i] = ReadOneByte(addr+i);
	}
}

/*******************************************************************************
* 函数名   		: UpVarTmp
* 功能			: 更新var_tmp缓存数组
* 输入			: mode 1 Date to var_tmp  0 var_tmp to Date
* 输出			: 无
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
* 函数名   		: ClearVarTmp
* 功能			: 清空var_tmp缓存数组
* 输入			: var_tmp数组大小
* 输出			: 无
*******************************************************************************/
void ClearVarTmp(uint SIZE)
{
	int i;
	for(i=0;i<SIZE;i++)
	{
		var_tmp[i]=0;
	}
}
