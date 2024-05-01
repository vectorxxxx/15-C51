#include <REGX52.H>
#include "Delay.h"
#include "Key.h"
#include "Timer0.h"
#include "Nixie.h"
#include "Motor.h"
#include "IR.h"

// 速度档位
unsigned char Speed;
// 红外遥控命令码
unsigned char Command;

void main()
{
    Motor_Init();
    IR_Init();
    
    while(1)
    {
        if(IR_GetDataFlag())
        {
            Command=IR_GetCommand();
            
            if(Command==IR_0) Speed=0;
            else if(Command==IR_1) Speed=1;
            else if(Command==IR_2) Speed=2;
            else if(Command==IR_3) Speed=3;
            
            Motor_SetSpeed(Speed);
        }
        
        Nixie(1,Speed);
    }
}
