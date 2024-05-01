#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"
#include "LCD1602.h"
#include "IR.h"

unsigned char Address, Command;
unsigned char Num;

void main()
{
    LCD1602_Init();
    LCD1602_ShowStr(1, 1, "ADD");
    LCD1602_ShowStr(1, 6, "COM");
    LCD1602_ShowStr(1, 11, "NUM");
    LCD1602_ShowNum(2, 1, 0, 2);
    LCD1602_ShowHexNum(2, 6, 0, 2);
    LCD1602_ShowNum(2, 11, 0, 3);

    IR_Init();

    while (1)
    {
        if (IR_GetDataFlag() || IR_GetRepeatFlag())
        {
            Address = IR_GetAddress();
            Command = IR_GetCommand();

            if (Command == IR_VOL_MINUS)
                Num--;
            else if (Command == IR_VOL_ADD)
                Num++;

            LCD1602_ShowNum(2, 1, Address, 2);
            LCD1602_ShowHexNum(2, 6, Command, 2);
            LCD1602_ShowNum(2, 11, Num, 3);
        }
    }
}