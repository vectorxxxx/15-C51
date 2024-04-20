#include "LCD1602.h"

// 显示密码
void ShowPassWord(unsigned int PassWord)
{
    LCD_ShowNum(2,1,PassWord,4);
}