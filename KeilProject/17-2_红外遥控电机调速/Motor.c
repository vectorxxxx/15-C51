#include <REGX52.H>
#include "Timer1.h"

// 电机引脚定义
sbit Motor=P1^0;

// PWM模型：计数器、比较值
unsigned char Counter,Compare;

void Motor_Init()
{
    Timer1_Init();
}

/**
  * @brief 设置速度档位
  * @param  无
  * @retval 无
  */
void Motor_SetSpeed(unsigned char Speed)
{
    // 速度档位与比较值对应关系，速度档位决定占空比
    if(Speed==0) Compare=0;
    else if(Speed==1) Compare=50;
    else if(Speed==2) Compare=75;
    else if(Speed==3) Compare=100;
}

/**
  * @brief 定时器1终端执行程序
  * @param  无
  * @retval 无
  */
void Timer1_Routine() interrupt 3
{
    static unsigned int Counter;
    
    // 重置定时器初始值
	TL1 = 0xA4;				//设置定时初始值
	TH1 = 0xFF;				//设置定时初始值

    // 中断1次为100us，100次即10ms
    Counter++;
    Counter%=100;
    
    // PWM输出
    if(Counter<Compare)
    {
        Motor=1; //电机转动为1，停止为0
    }
    else
    {
        Motor=0; //电机转动为1，停止为0
    }
}