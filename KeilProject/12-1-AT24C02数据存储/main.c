#include <REGX52.H>
#include "LCD1602.h"
#include "Key.h"
#include "Delay.h"
#include "AT24C02.h"

unsigned char KeyNum;
unsigned int Num;

void main()
{
    LCD_Init();
    LCD_ShowNum(1,1,Num,5);
    while(1)
    {
        KeyNum=Key();
        if(KeyNum==1)
        {
            Num++;
            LCD_ShowNum(1,1,Num,5);
        }
        else if(KeyNum==2)
        {
            Num--;
            LCD_ShowNum(1,1,Num,5);
        }
        else if(KeyNum==3)
        {
            AT24C02_WriteData(0,Num%256);
            Delay(5);
            AT24C02_WriteData(1,Num/256);
            Delay(5);
            LCD_ShowString(2,1,"Write OK");
            Delay(1000);
            LCD_ShowString(2,1,"        ");
        }
        else if(KeyNum==4)
        {
            Num=AT24C02_ReadData(0);
            Num|=AT24C02_ReadData(1)<<8;
            LCD_ShowNum(1,1,Num,5);
            LCD_ShowString(2,1,"Read OK");
            Delay(1000);
            LCD_ShowString(2,1,"       ");
        }
    }
}

// 测试
// unsigned char Data;
//void main()
//{
//    LCD_Init();
//    LCD_ShowString(1,1,"Hello");
//    AT24C02_WriteData(0,69);
//    // 写周期tWR=5ms, 写入需要点时间，所以进行延时
//    Delay(5);
//    Data=AT24C02_ReadData(0);
//    LCD_ShowNum(2,1,Data,3);
//    while(1)
//    {
//        
//    }
//}