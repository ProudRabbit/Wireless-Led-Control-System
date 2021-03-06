# Wireless-Led-Control-System

## 无线路灯控制系统

### 1 . 主机配置使用说明：

> **1. 主机按键配置**
>
> > 主机使用KEY1按键（P2.0）进入配置模式。  
> > 使用KEY2按键（P2.1）增加数值。  
> > 使用KEY3按键（P2.2）减少数值。  
> > 使用KEY4按键（P2.3）确定，并进入下一项参数配置。  
> > 以上任意时刻，使用KEY1按键都可退出配置模式，参数不保存。  
>
> **2. 主机参数配置说明**
>
> > 按下KEY1，进入配置模式后，第一个显示的数值为总倒计时时间。  
> > 按下KEY4后，显示的数值为下发第一条命令的时间。  
> > 再次按下KEY4后，显示的数值为下发第二条命令的时间。  
> > 再次按下KEY4后，显示的数值为下发第三条命令的时间。  
> > 再次按下KEY4后，退出配置模式，并保存参数。  
>
> **3. 主机数码管配置**
>
> > 可在`sys.h`头文件中配置数码管使用的IO口。  
> > 通过`#define DIG_PLACE_SELECT	0`宏定义可以配置数码管位选为阳极还是阴极接法。  
> > 通过`#define DIG_CODE_SELECT 	0`宏定义可以配置数码管段选为共阳极还是共阴极接法。  
> > 数码管的位选采用线选法驱动，未使用译码器。  
>
> **4. 主机IIC接口配置**
>
>  > 在`sys.h`文件中配置SCL和SDA使用的IO口。  

---
### 2. 从机配置说明

>  **1. 从机按键配置**
>  
>  > 和主机按键使用的IO一样。
>
>  **2. 从机参数配置说明**
>  
>  > a.  配置为奇数模式
>  >
>  > > 按下KEY1，进入配置模式后，LED8点亮（P0.8）标志已经进入配置模式。  
>  > > 按下KEY2后，LED1点亮，表示已经配置从机为奇数点亮模式。  
>  > > 再次按下KEY1后，退出配置模式LED8熄灭（P0.8）。  
>  >
>  > b.  配置为偶数模式
>  > 
>  > > 按下KEY1，进入配置模式后，LED8点亮（P0.8）标志已经进入配置模式。  
>  > > 按下KEY2后，LED0点亮，表示已经配置从机为偶数点亮模式。  
>  > > 再次按下KEY1后，退出配置模式LED8熄灭（P0.8）。   
> 
> **3. 从机IIC接口配置**
> 
> > 同主机一样，在`sys.h`文件中配置SCL和SDA所使用的IO口。   

---
### 3. 通讯协议说明
> 帧头：0x39；  
> 帧尾：0x93；  
> 无校验  
> 波特率：9600；  
> 晶振频率：11.0592MHZ；  
> 串口数据缓存放在 str[USART_SIZE] 中，大小为`#define USART_SIZE 6`由于发送数据不多，不需要修改。  

---
### 4. BUG

> ~~由于目前使用的芯片没有片内EEPROM，配置的参数依旧保持在RAM中，复位后丢失。~~

---
### 5. 日志

3/30

> 使用IIC驱动AT24C02用来保存参数，解决了参数不能掉电保存的问题。 

---

3/25

>完成主机的手动配置功能
>
>~~发现的BUG：由于该芯片没有片内EEPROM，配置的参数依旧保持在RAM中，复位后丢失。~~
>
>由于上面的BUG，从机暂时不将参数写入ROM。
>

---

3/24
>完成串口协议的编写
>
>从机添加设备ID
>
>从机添加按键

---

3/23 

>添加了主从机的EEPROM  
>
>对文件的编码格式进行了转换 目前使用UTF8
>
>从机增加了LED

---

2/24
>添加了串口通讯
>
>添加了定时器
>
>添加了按键功能

---

2/19	添加了数码管显示功能

---

2/16	添加了主从机的原理图工程

---

2/15	完成主机和从机工程的构架

