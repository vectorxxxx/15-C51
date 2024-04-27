#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "DS18B20.h"

// unsigned char Ack;            // 调试用

float T;

void ShowT()
{
    // 正负
    if (T < 0)
    {
        LCD_ShowChar(2, 1, '-');
        T = -T;
    }
    else
    {
        LCD_ShowChar(2, 1, '+');
    }
    // 整数部分
    LCD_ShowNum(2, 2, T, 3);
    // 小数点
    LCD_ShowChar(2, 5, '.');
    // 小数部分
    LCD_ShowNum(2, 6, (unsigned long)(T * 10000) % 10000, 4);
}

void main()
{
    DS18B20_ConvertT(); // 上电先转换一次温度，防止第一次读数据错误
    Delay(750);         // 转换位数为12位时，最大转换时间为750ms。延迟等待转换完成
    LCD_Init();
    LCD_ShowString(1, 1, "Temperature:");

    // Ack=OneWire_Init();       // 调试用
    // LCD_ShowNum(2,1,Ack,3);   // 调试用

    while (1)
    {
        DS18B20_ConvertT();  // 转换温度
        T = DS18B20_ReadT(); // 读取温度
        ShowT();
    }
}
