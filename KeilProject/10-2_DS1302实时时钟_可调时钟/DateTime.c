#include "LCD1602.h"
#include "DS1302.h"

const char *WeekDay[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

void ShowYear()
{
    LCD_ShowNum(1,1,DS1302_DateTime[0],2);
}

void ShowMonth()
{
    LCD_ShowNum(1,4,DS1302_DateTime[1],2);
}

void ShowDate()
{
    LCD_ShowNum(1,7,DS1302_DateTime[2],2);
}

void ShowHour()
{
    LCD_ShowNum(2,1,DS1302_DateTime[3],2);
}

void ShowMinute()
{
    LCD_ShowNum(2,4,DS1302_DateTime[4],2);
}

void ShowSecond()
{
    LCD_ShowNum(2,7,DS1302_DateTime[5],2);
}

void ShowDay()
{
    LCD_ShowString(1,10,WeekDay[DS1302_DateTime[6]%7]);
}

void ClearYear()
{
    LCD_ShowString(1,1,"  ");
}

void ClearMonth()
{
    LCD_ShowString(1,4,"  ");
}

void ClearDate()
{
    LCD_ShowString(1,7,"  ");
}

void ClearHour()
{
    LCD_ShowString(2,1,"  ");
}

void ClearMinute()
{
    LCD_ShowString(2,4,"  ");
}

void ClearSecond()
{
    LCD_ShowString(2,7,"  ");
}

void ClearDay()
{
    LCD_ShowString(1,10,"   ");
}

/**
  * @brief 显示日期时间
  * @param  无
  * @retval 无
  */
void ShowDateTime()
{
    DS1302_GetDateTime();
    
    ShowYear();
    ShowMonth();
    ShowDate();
    ShowHour();
    ShowMinute();
    ShowSecond();
    ShowDay();
}

/**
  * @brief 闪烁日期时间
  * @param  无
  * @retval 无
  */
void FlickerDateTime(unsigned char TimerSelect,FlickerFlag)
{
    if(TimerSelect==0 && FlickerFlag==1) ClearYear();
    else ShowYear();
    
    if(TimerSelect==1 && FlickerFlag==1) ClearMonth();
    else ShowMonth();
    
    if(TimerSelect==2 && FlickerFlag==1) ClearDate();
    else ShowDate();
    
    if(TimerSelect==3 && FlickerFlag==1) ClearHour();
    else ShowHour();
    
    if(TimerSelect==4 && FlickerFlag==1) ClearMinute();
    else ShowMinute();
    
    if(TimerSelect==5 && FlickerFlag==1) ClearSecond();
    else ShowSecond();
    
    if(TimerSelect==6 && FlickerFlag==1) ClearDay();
    else ShowDay();
}


/**
  * @brief 获取二月天数
  * @param  无
  * @retval 无
  */
unsigned char GetFebruaryDay()
{
    char Year=DS1302_DateTime[0];
    
    // 大闰年
    if(Year%400 == 0)
        return 29;
    // 小闰年
    else if(Year%4 == 0 && Year%100 != 0) 
        return 29;
    // 非闰年
    else 
        return 28;
}

/**
  * @brief 重置范围
  * @param  无
  * @retval 无
  */
char ResetRange(char Temp,Min,Max)
{
    if(Temp>Max) Temp=Min;
    if(Temp<Min) Temp=Max;
    return Temp;
}

/**
  * @brief 根据月份重置天数
  * @param  无
  * @retval 无
  */
void ResetDateByMonth()
{
    char Month=DS1302_DateTime[1];
    char Date=DS1302_DateTime[2];
    
    switch(Month)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            Date=ResetRange(Date,1,31);
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            Date=ResetRange(Date,1,30);
            break;
        case 2:
            Date=ResetRange(
                Date,
                1,
                GetFebruaryDay()
            );
            break;
    }
    
    DS1302_DateTime[2]=Date;
}

/**
  * @brief 校正日期时间
  * @param  无
  * @retval 无
  */
void AdjustDateTime(unsigned char TimerSelect)
{
    if(TimerSelect==0)
    {
        DS1302_DateTime[TimerSelect]=ResetRange(
            DS1302_DateTime[TimerSelect],
            0,99
        );
        ResetDateByMonth();
    }
    else if(TimerSelect==1)
    {
        DS1302_DateTime[TimerSelect]=ResetRange(
            DS1302_DateTime[TimerSelect],
            1,12
        );
        ResetDateByMonth();
    }
    else if(TimerSelect==2)
    {
        ResetDateByMonth();
    }
    else if(TimerSelect==3)
    {
        DS1302_DateTime[TimerSelect]=ResetRange(
            DS1302_DateTime[TimerSelect],
            0,23
        );
    }
    else if(TimerSelect==4 || TimerSelect==5)
    {
        DS1302_DateTime[TimerSelect]=ResetRange(
            DS1302_DateTime[TimerSelect],
            0,59
        );
    }
    else if(TimerSelect==6)
    {
        DS1302_DateTime[TimerSelect]=ResetRange(
            DS1302_DateTime[TimerSelect],
            0,6
        );
    }
}

/**
  * @brief 调大日期时间
  * @param  无
  * @retval 无
  */
void IncreaseDateTime(unsigned char TimerSelect)
{
    DS1302_DateTime[TimerSelect]++;
    AdjustDateTime(TimerSelect);
}

/**
  * @brief 调小日期时间
  * @param  无
  * @retval 无
  */
void DecreaseDateTime(unsigned char TimerSelect)
{
    DS1302_DateTime[TimerSelect]--;
    AdjustDateTime(TimerSelect);
}
