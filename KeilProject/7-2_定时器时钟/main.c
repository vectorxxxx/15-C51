#include <REGX52.H>
#include "Timer0.h"
#include "LCD1602.h"
#include "DateTime.h"

unsigned int year=2024,month=4,day=30,hour=23,minute=59,second=56;

/**
  * @brief 计算日期时间
  * @param  无
  * @retval 无
  */
void CalcDateTime()
{
    if(++second<60) return;
    second=0;

    if(++minute<60) return;
    minute=0;

    if(++hour<24) return;
    hour=0;
    
    if(++day<=GetDay(year, month)) return;
    day=1;

    if(++month<=12) return;
    month=1;

    if(++year<=9999) return;
    year=1;
}

/**
  * @brief 显示日期时间
  * @param  无
  * @retval 无
  */
void ShowDateTime()
{
    LCD_ShowNum(1,1,year,4);
    LCD_ShowNum(1,6,month, 2);
    LCD_ShowNum(1,9,day,2);
    LCD_ShowNum(2,1,hour,2);
    LCD_ShowNum(2,4,minute,2);
    LCD_ShowNum(2,7,second,2);
}

void main()
{
    // 初始化
    LCD_Init();
    Timer0_Init();
    
    // 显示固定内容
    LCD_ShowString(1,1,"    -  -");
    LCD_ShowString(2,1,"  :  :");
	while(1)
	{
        // 显示日期时间
		ShowDateTime();
	}
}

void Timer0_Rountine() interrupt 1
{
    static unsigned int Counter;
    
    // 重置定时器初始值
	TL0 = 0x66;
	TH0 = 0xFC;
    
    // 中断1次为1ms，500次即0.5s
    if(++Counter>=1000)
    {
        Counter=0;
        
        // 计算日期时间
        CalcDateTime();
    }
}