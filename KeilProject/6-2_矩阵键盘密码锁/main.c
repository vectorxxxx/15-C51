#include <REGX52.H>
#include "LCD1602.h"
#include "PassWordLock.h"

void main()
{
    LCD_Init();
    LCD_ShowString(1,1,"PassWord:");
	while(1)
	{
        PassWordLock();
	}
}