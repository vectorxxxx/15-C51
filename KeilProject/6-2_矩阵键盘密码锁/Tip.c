#include "LCD1602.h"

// 显示提示
void ShowTip(char *Tip)
{
    LCD_ShowString(1,14,Tip);
}

// 显示成功
void ShowOK()
{
    ShowTip("OK ");
}

// 显示失败
void ShowERR()
{
    ShowTip("ERR ");
}

// 清除提示
void ShowNth()
{
    ShowTip("   ");
}