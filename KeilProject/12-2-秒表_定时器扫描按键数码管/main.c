#include <REGX52.H>
#include "Timer0.h"
#include "Key.h"
#include "Nixie.h"
#include "AT24C02.h"
#include "Delay.h"

unsigned char KeyNum;
unsigned char ChronometerStatus;
unsigned char Min,Sec,MiniSec;

/**
  * @brief 开始/暂停秒表
  * @param  无
  * @retval 无
  */
void Chronometer_Start_Pause()
{
    ChronometerStatus=!ChronometerStatus;
}

/**
  * @brief 重置秒表
  * @param  无
  * @retval 无
  */
void Chronometer_Reset()
{
    Min=0;
    Sec=0;
    MiniSec=0;
}

/**
  * @brief 保存秒表
  * @param  无
  * @retval 无
  */
void Chronometer_Save()
{
    AT24C02_WriteData(0,Min);
    Delay(5); // 很重要
    AT24C02_WriteData(1,Sec);
    Delay(5); // 很重要
    AT24C02_WriteData(2,MiniSec);
    Delay(5); // 很重要
}

/**
* @brief 恢复秒表
  * @param  无
  * @retval 无
  */
void Chronometer_Recover()
{
    Min=AT24C02_ReadData(0);
    Sec=AT24C02_ReadData(1);
    MiniSec=AT24C02_ReadData(2);
}

/**
  * @brief 显示秒表
  * @param  无
  * @retval 无
  */
void Chronometer_Show()
{
    Nixie(1,Min/10);
    Nixie(2,Min%10);
    Nixie(3,10);
    Nixie(4,Sec/10);
    Nixie(5,Sec%10);
    Nixie(6,10);
    Nixie(7,MiniSec/10);
    Nixie(8,MiniSec%10); 
}

void main()
{
    Timer0_Init();
    while(1)
    {
        KeyNum=Key();
        
        // 开始/暂停
        if(KeyNum==1) Chronometer_Start_Pause();
        // 重置
        else if(KeyNum==2) Chronometer_Reset();
        // 保存
        else if(KeyNum==3) Chronometer_Save();
        // 恢复
        else if(KeyNum==4) Chronometer_Recover();
        
        // 数码管显示秒表
        Chronometer_Show();
    }
}

/**
  * @brief 秒表定时执行程序
  * @param  无
  * @retval 无
  */
void Chronometer_Loop(void)
{
    if(!ChronometerStatus) return;
    
    if(++MiniSec<100) return;
    MiniSec=0;
    
    if(++Sec<60) return;
    Sec=0;
    
    if(++Min<60) return;
    Min=0;
}

/**
  * @brief 定时器0中断程序
  * @param  无
  * @retval 无
  */
void Timer0_Routine() interrupt 1
{
    static unsigned int Counter1,Counter2,Counter3;

    // 重置定时器初始值
    TL0 = 0x66;
    TH0 = 0xFC;

    // 驱动独立按键
    if(++Counter1>=20)
    {
        Counter1=0;
        Key_Loop();
    }
    
    // 驱动数码管
    if(++Counter2>=2)
    {
        Counter2=0;
        Nixie_Loop();
    }

    // 驱动秒表
    if(++Counter3>=10)
    {
        Counter3=0;
        Chronometer_Loop();
    }
}