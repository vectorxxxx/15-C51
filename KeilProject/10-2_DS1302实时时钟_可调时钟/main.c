#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Key.h"
#include "Timer0.h"
#include "DateTime.h"

unsigned char KeyNum,MODE,TimerSelect,FlickerFlag;

/**
  * @brief 初始化
  * @param  无
  * @retval 无
  */
void Init()
{
    LCD_Init();
    DS1302_Init();
    Timer0_Init();
    
    LCD_ShowString(1,1,"  -  -  ");
    LCD_ShowString(2,1,"  :  :  ");
    
    DS1302_SetDateTime();
}

/**
  * @brief 修改日期时间
  * @param  无
  * @retval 无
  */
void EditDateTime()
{
    // 选择日期时间
    if(KeyNum==2)
    {
        TimerSelect++;
        TimerSelect%=7;
    }
    // 调大日期时间
    if(KeyNum==3)
    {
        IncreaseDateTime(TimerSelect);
    }
    // 调小日期时间
    if(KeyNum==4)
    {
        DecreaseDateTime(TimerSelect);
    }
    
    // 闪烁日期时间
    FlickerDateTime(TimerSelect,FlickerFlag);
}

/**
  * @brief 选择模式
  * @param  无
  * @retval 无
  */
void SelectMode()
{
    KeyNum=Key();
    
    // 选择模式
    if(KeyNum==1)
    {
        // 修改为编辑模式
        if(MODE==0)
        {
            MODE=1;
            TimerSelect=0;
        }
        // 修改为显示模式
        else if(MODE==1)
        {
            MODE=0;
            DS1302_SetDateTime();
        }
    }
    
    // 显示模式
    if(MODE==0)
    {
        ShowDateTime();
    }
    // 编辑模式
    else if(MODE==1)
    {
        EditDateTime();
    }
}

void main()
{
    Init();
    while(1)
    {
        // 选择模式
        SelectMode();

//        LCD_ShowNum(2,10,KeyNum,1);
//        LCD_ShowNum(2,12,MODE,1);
//        LCD_ShowNum(2,14,TimerSelect,1);
//        LCD_ShowNum(2,16,FlickerFlag,1);        
    }
}

/**
  * @brief 定时器0终端执行程序
  * @param  无
  * @retval 无
  */
void Timer0_Routine() interrupt 1
{
    static unsigned int Counter;
    
    // 重置定时器初始值
	TL0 = 0x66;
	TH0 = 0xFC;
    
    // 中断1次为1ms，500次即0.5s
    if(++Counter>=500)
    {
        Counter=0;
   
        FlickerFlag=!FlickerFlag;
    }
}
