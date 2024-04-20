## 1、Timer0

`Timer0.h`

```c
#ifndef __TIMER0_H__
#define __TIMER0_H__

void Timer0_Init(void);

#endif
```

`Timer0.c`

```c
#include <REGX52.H>

/**
  * @brief 定时器0初始化，1毫秒@11.0592MHz
  * @param  无
  * @retval 无
  */
void Timer0_Init(void)
{
    // 1、设置定时器/计数器工作模式寄存器TMOD
    //       7     6    5    4      3      2    1    0
    //   |======================||======================|
    //   | GATE | C/T | M1 | M0 || GATE | C/T | M1 | M0 |
    //   |========定时器1=======||=======定时器0========|
    //    M1    MO  定时器定时器/计数器1模式选择
    //    0     0   13位定时器/计数器，兼容8048定时模式，TL1只用低5位参与分频，TH1整个8位全用。
    //    0     1   16位定时器/计数器，TL1、TH1全用
    //    1     0   8位自动重装载定时器，当溢出时将TH1存放的值自动重装入TL1.
    //    1     1   定时器/计数器1此时无效（停止计数）。
	TMOD &= 0xF0;   // 高4位不变，低4位清零
	TMOD |= 0x01;   // 高4位不变，低4位置一
    
    
    // 2、设置计数器0初始值
	TL0 = 0x66;     // Timer Low  0（8bit）
	TH0 = 0xFC;     // Timer High 0（8bit）
    
    
    // 3、定时器/计数器0控制寄存器TCON
    //      B7   B6    B5    B4     B3    B2    B1    B0
    //   |=======================||=======================|
    //   | TF1 | TR1 | TF0 | TR0 || IE1 | IT1 | IE0 | IT0 |
    //   |=======================||=======================|
	TF0 = 0;    // 定时器0溢出中断标志置0
	TR0 = 1;    // 定时器0的运行控制位置1
    
    
    // 4、中断允许寄存器IE和XICON
    //     B7   B6  B5    B4    B3    B2    B1    B0
    //   |===================||=======================|
    //   | EA | - | ET2 | ES || ET1 | EX1 | ET0 | EX0 |
    //   |===================||=======================|
    ET0=1;      // T0的溢出中断允许位
    EA=1;       // CPU的总中断允许控制位
    
    
    // 5、中断优先级控制寄存器IP/XICON和IPH
    //          IPH：中断优先级控制寄存器高（不可位寻址）
    //      B7     B6    B5    B4      B3     B2     B1     B0
    //   |=========================||===========================|
    //   | PX3H | PX2H | PT2 | PSH || PT1H | PX1H | PT0H | PX0H |
    //   |=========================||===========================|
    //
    //          XICON：辅助中断控制寄存器  （可位寻址）
    //     B7    B6    B5    B4     B3    B2    B1    B0
    //   |=======================||=======================|
    //   | PX3 | EX3 | IE3 | IT3 || PX2 | EX2 | IE2 | IT2 |
    //   |=======================||=======================|
    //
    //          IP:中断优先级控制寄存器低 （可位寻址）
    //     B7  B6  B5    B4    B3    B2    B1    B0
    //   |==================||=======================|
    //   | - | - | PT2 | PS || PT1 | PX1 | PT0 | PX0 |
    //   |==================||=======================|
    PT0=0;
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

定时器0终端执行程序
void Timer0_Routine() interrupt 0
{
    static unsigned int Counter;
    
    // 中断1次为1ms，1000次即1s
    if(++Counter>=1000)
    {
        Counter=0;
   
        // TODO
    }
}
*/
```

无注释版

```c
#include <REGX52.H>

void Timer0_Init(void)
{
	TMOD &= 0xF0;
	TMOD |= 0x01;
	TL0 = 0x66;
	TH0 = 0xFC;
	TF0 = 0;
	TR0 = 1;
    ET0=1;
    EA=1;
    PT0=0;
}
```

## 2、Key

`Key.h`

```c
#ifndef __KEY_H__
#define __KEY_H__

unsigned char Key(void);

#endif
```

`Key.c`

```c
#include <REGX52.H>
#include "Delay.h"
/**
  * @brief 获取独立按键键码
  * @param  无
  * @retval 范围0~4，默认无按键按下为0
  */
unsigned char Key(void)
{
    unsigned char KeyNum=0;
    
    if(P3_1==0){Delay(20);while(P3_1==0)Delay(20);KeyNum=1;}
    if(P3_0==0){Delay(20);while(P3_0==0)Delay(20);KeyNum=2;}
    if(P3_2==0){Delay(20);while(P3_2==0)Delay(20);KeyNum=3;}
    if(P3_3==0){Delay(20);while(P3_3==0)Delay(20);KeyNum=4;}
    
    return KeyNum;
}
```

## 3、Main

```c
#include <REGX52.H>
#include "Timer0.h"
#include "Key.h"
#include <INTRINS.H>

unsigned char KeyNum,LEDMode;

/**
  * @brief 独立按键控制LED
  * @param  无
  * @retval 无
  */
void ChangeLEDMode()
{
    KeyNum=Key();
    if(!KeyNum) return;
    
    if(KeyNum==1)
    {
        LEDMode = LEDMode==1 ? 0 : 1;
    }
}

/**
  * @brief LED按照指定模式运行
  * @param  无
  * @retval 无
  */
void LightLED()
{
    if(LEDMode==1) 
        P2=_cror_(P2,1);
    else 
        P2=_crol_(P2,1);
}

void main()
{
    Timer0_Init();
    P2=0xFE;
	while(1)
	{
		ChangeLEDMode();
	}
}

void Timer0_Rountine() interrupt 1
{
    static unsigned int Counter;
    
    // 重置定时器初始值
	TL0 = 0x66;
	TH0 = 0xFC;
    
    // 中断1次为1ms，500次即0.5s
    if(++Counter>=500)
    {
        Counter=0;

        LightLED();
    }
}
```

