#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"

// LED灯引脚定义
sbit DA=P2^1;

// PWM模型：计数器、比较值
unsigned char Counter,Compare;

void main()
{
    unsigned char i;
    Timer0_Init();
    while(1)
    {
        for(i=0;i<100;i++)
		{
			Compare=i;			//设置比较值，改变PWM占空比
			Delay(10);
		}
		for(i=100;i>0;i--)
		{
			Compare=i;			//设置比较值，改变PWM占空比
			Delay(10);
		}
    }
}

void Timer0_Routine() interrupt 1
{
    static unsigned int Counter;
    
    // 重置定时器初始值
	TL0 = 0xA4;				//设置定时初始值
	TH0 = 0xFF;				//设置定时初始值

    // 中断1次为100us，100次即10ms
    Counter++;
    Counter%=100;
    
    // PWM输出
    if(Counter<Compare)
    {
        DA=1; //电机转动为1，停止为0
    }
    else
    {
        DA=0; //电机转动为1，停止为0
    }
}