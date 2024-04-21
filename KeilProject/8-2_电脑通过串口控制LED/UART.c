#include <STC89C5xRC.H>

/**
  * @brief 串口初始化，4800bps@11.0592MHz
  * @param  无
  * @retval 无
  */
void UART_Init()
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率

	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式

	TL1 = 0xF4;			//设置定时初始值
	TH1 = 0xF4;			//设置定时重载值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
    
    EA = 1;             //启用CPU总中断
    ES = 1;             //启用串口中断
}

/**
  * @brief 串口向电脑发送字节数据
  * @param  一个字节的Byte数据
  * @retval 无
  */
void UART_SendByte(unsigned int Byte)
{
    SBUF=Byte;
    while(TI==0);
    TI=0;
}

/*
void Int0_Routine(void)     interrupt 0;
void Timer0_Rountine(void)  interrupt 1;
void Int1_Routine(void)     interrupt 2;
void Timer1_Rountine(void)  interrupt 3:
void UART_Routine(void)     interrupt 4;
void Timer2_Routine(void)   interrupt 5;
void Int2_Routine(void)     interrupt 6;
void Int3_Routine(void)     interrupt 7;

串口中断子函数模板
void UART_Routine(void)     interrupt 4
{
    if(RI==1)
    {
        // TODO
        
        RI=0;
    }
}
*/