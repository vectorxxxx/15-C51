#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"

const char *WeekDay[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

void main()
{
    LCD_Init();
    DS1302_Init();
    
    LCD_ShowString(1,1,"  -  -  ");
    LCD_ShowString(2,1,"  :  :  ");
    
    DS1302_SetTime();
    while(1)
    {
        DS1302_GetTime();

        LCD_ShowNum(1,1,DS1302_DateTime[0],2);
        LCD_ShowNum(1,4,DS1302_DateTime[1],2);
        LCD_ShowNum(1,7,DS1302_DateTime[2],2);
        
        LCD_ShowString(1,10,WeekDay[DS1302_DateTime[6]%7]);
        
        LCD_ShowNum(2,1,DS1302_DateTime[3],2);
        LCD_ShowNum(2,4,DS1302_DateTime[4],2);
        LCD_ShowNum(2,7,DS1302_DateTime[5],2);
    }
}
