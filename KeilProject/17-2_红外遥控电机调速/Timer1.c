#include <REGX52.H>

/**
  * @brief 定时器1初始化，1毫秒@11.0592MHz
  * @param  无
  * @retval 无
  */
void Timer1_Init(void)
{
	TMOD &= 0x0F;			//设置定时器模式
	TMOD |= 0x10;			//设置定时器模式
	TL1 = 0xA4;				//设置定时初始值
	TH1 = 0xFF;				//设置定时初始值
	TF1 = 0;				//清除TF1标志
	TR1 = 1;				//定时器1开始计时
    ET1=1;                  // T1的溢出中断允许位
    EA=1;                   // CPU的总中断允许控制位
    PT1=0;
}

// 定时器1终端执行程序
//void Int0_Routine(void)     interrupt 0;
//void Timer0_Rountine(void)  interrupt 1;
//void Int1_Routine(void)     interrupt 2;
//void Timer1_Rountine(void)  interrupt 3:
//void UART_Routine(void)     interrupt 4;
//void Timer2_Routine(void)   interrupt 5;
//void Int2_Routine(void)     interrupt 6;
//void Int3_Routine(void)     interrupt 7;
//void Timer1_Routine() interrupt 3
//{
//    static unsigned int Counter;
//    
//    // 重置定时器初始值
//	TL1 = 0x66;
//	TH1 = 0xFC;

//    // 中断1次为1ms，1000次即1s
//    if(++Counter>=1000)
//    {
//        Counter=0;
//   
//        // TODO
//    }
//}