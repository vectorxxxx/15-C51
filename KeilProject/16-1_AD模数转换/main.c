#include <REGX52.H>
#include "LCD1602.h"
#include "Key.h"
#include "XPT2046.h"
#include "Delay.h"

unsigned int ADValue;
unsigned char Resolution=8;
unsigned char KeyNum;

void main()
{
    LCD_Init();
    LCD_ShowString(1,1,"ADJ");  // Adjustable
    LCD_ShowString(1,6,"NTC");  // Negative Temperature Coefficient（负温度系数）热敏电阻
    LCD_ShowString(1,11,"GR");  
    LCD_ShowNum(1,15,Resolution,2);
    while(1)
    {
        // 按键切换分辨率
        KeyNum=Key();
        if(KeyNum==1) 
        {
            if(Resolution==8) 
            {
                Resolution=12;
            }
            else if(Resolution==12) 
            {
                Resolution=8;
            }
            LCD_ShowNum(1,15,Resolution,2);
        }
            
        // 读取AIN0，可调电阻
        ADValue=XPT2046_ReadAD(XPT2046_XP,Resolution);      
        LCD_ShowNum(2,1,ADValue,4);
        // 读取AIN1，热敏电阻
        ADValue=XPT2046_ReadAD(XPT2046_YP,Resolution);      
        LCD_ShowNum(2,6,ADValue,4);
        // 读取AIN2，光敏电阻
        ADValue=XPT2046_ReadAD(XPT2046_VBAT,Resolution);    
        LCD_ShowNum(2,11,ADValue,4);
        Delay(200);
    }
}
