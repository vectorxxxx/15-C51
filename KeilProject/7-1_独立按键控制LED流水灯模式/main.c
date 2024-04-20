#include <REGX52.H>
#include "Timer0.h"
#include "Key.h"
#include <INTRINS.H>

unsigned char KeyNum,LEDMode;

/**
  * @brief 独立按键控制LED
  * @param  无
  * @retval 无
  */
void ChangeLEDMode()
{
    KeyNum=Key();
    if(!KeyNum) return;
    
    if(KeyNum==1)
    {
        LEDMode = LEDMode==1 ? 0 : 1;
    }
}

/**
  * @brief LED按照指定模式运行
  * @param  无
  * @retval 无
  */
void LightLED()
{
    if(LEDMode==1) 
        P2=_cror_(P2,1);
    else 
        P2=_crol_(P2,1);
}

void main()
{
    Timer0_Init();
    P2=0xFE;
	while(1)
	{
		ChangeLEDMode();
	}
}

void Timer0_Rountine() interrupt 1
{
    static unsigned int Counter;
    
    // 重置定时器初始值
	TL0 = 0x66;
	TH0 = 0xFC;
    
    // 中断1次为1ms，500次即0.5s
    if(++Counter>=500)
    {
        Counter=0;

        LightLED();
    }
}