#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "DS18B20.h"
#include "AT24C02.h"
#include "Key.h"
#include "Timer0.h"

float T,Tmp;
char THigh,TLow;
unsigned char KeyNum;

/**
  * @brief 从DS18B20中读取温度并显示
  * @param  无
  * @retval 无
  */
void ShowT()
{
    DS18B20_ConvertT();	    //转换温度
    T=DS18B20_ReadT();	    //读取温度
    
    // 正负部分
    LCD_ShowChar(1,1,T<0 ? '-' : '+');
    Tmp=T<0 ? -T : T;
    // 整数部分
    LCD_ShowNum(1,2,Tmp,3);
    // 小数部分
    LCD_ShowNum(1,6,(unsigned long)(Tmp*100)%100,2);   
}

/**
  * @brief 从E2PROM中读取阈值并显示
  * @param  无
  * @retval 无
  */
void ShowThreshold()
{
    // 读出阈值
    THigh=AT24C02_ReadData(0);
    TLow=AT24C02_ReadData(1);
    if(!THigh) THigh=25;
    if(!TLow) TLow=20;
    
    // 显示阈值
    LCD_ShowSignedNum(2,4,THigh,3);
    LCD_ShowSignedNum(2,13,TLow,3);
}

/**
  * @brief 显示警报
  * @param  无
  * @retval 无
  */
void ShowAlarm()
{
    if(T>=THigh) LCD_ShowString(1,13,"OV:H");
    else if(T<=TLow) LCD_ShowString(1,13,"OV:L");
    else LCD_ShowString(1,13,"    ");
}

/**
  * @brief 调节温度报警阈值，温度可测量范围为： -55℃至+125℃
  * @param  无
  * @retval 无
  */
void AdjustThreshold()
{
    KeyNum=Key();
    if(!KeyNum) return;
    LCD_ShowNum(1,10,KeyNum,1);
    
    // 调节阈值
    if(KeyNum==1 && THigh<125) THigh++;
    else if(KeyNum==2 && THigh>TLow+1) THigh--;
    else if(KeyNum==3 && TLow<THigh-1) TLow++;
    else if(KeyNum==4 && TLow>-55) TLow--;
    
    // 显示阈值
    LCD_ShowSignedNum(2,4,THigh,3);
    LCD_ShowSignedNum(2,13,TLow,3);
    
    // 保存阈值
    AT24C02_WriteData(0,THigh);
    Delay(5); // 写周期最大值5ms
    AT24C02_WriteData(1,TLow);
    Delay(5); // 写周期最大值5ms
    
    // 显示警报
    ShowAlarm();
}

void main()
{    
    DS18B20_ConvertT();         // 上电先转换一次温度，防止第一次读数据错误
    Delay(1000);                // 转换位数为12位时，最大转换时间为750ms。延迟等待转换完成
    
    Timer0_Init();
    
    LCD_Init();
    LCD_ShowChar(1,5,'.');
    LCD_ShowString(2,1,"TH:");
    LCD_ShowSignedNum(2,4,THigh,3);
    LCD_ShowString(2,10,"TL:");
    LCD_ShowSignedNum(2,13,TLow,3);

    ShowThreshold();            // 显示阈值
    ShowAlarm();                // 显示警报
    
    while(1)
    {
        // ######显示温度######
        ShowT();
        
        // ######调节阈值######
        AdjustThreshold();
    }
}

/**
  * @brief 定时器0中断程序
  * @param  无
  * @retval 无
  */
void Timer0_Routine() interrupt 1
{
    static unsigned int Counter;

    // 重置定时器初始值
    TL0 = 0x66;
    TH0 = 0xFC;

    // 中断1次为1ms
    if(++Counter>=20)
    {
        Counter=0;
        Key_Loop();
    }
}
