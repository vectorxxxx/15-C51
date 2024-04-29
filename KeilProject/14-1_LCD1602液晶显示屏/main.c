#include <REGX52.H>
#include "LCD1602.h"

void main()
{
    LCD1602_Init();
    LCD1602_ShowChar(1,1,'S');
    LCD1602_ShowChar(1,2,'B');
    LCD1602_ShowStr(1,4,"Fuck");
    LCD1602_ShowNum(1,9,567,3);
    LCD1602_ShowSignedNum(1,13,-895,3);
    LCD1602_ShowHexNum(2,1,0x5A,2);
    LCD1602_ShowBinNum(2,4,0x5A,8);
    LCD1602_ShowChar(2,13,0xDF);
    LCD1602_ShowChar(2,14,'C');
    while(1)
    {
	       
    }
}
