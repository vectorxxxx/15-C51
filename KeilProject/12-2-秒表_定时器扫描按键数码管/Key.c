#include <REGX52.H>
#include "Delay.h"

unsigned char Key_KeyNum;

/**
  * @brief 获取独立按键键码（滤波后）
  * @param  无
  * @retval 范围0~4，默认无按键按下为0
  */
unsigned char Key(void)
{
    // 返回后将KeyNum置0，防止产生干扰
    unsigned char TempKeyNum = Key_KeyNum;
    Key_KeyNum=0;
    return TempKeyNum;
}

/**
  * @brief 获取独立按键键码（滤波前）
  * @param  无
  * @retval 范围0~4，默认无按键按下为0
  */
unsigned char Key_GetState(void)
{
    unsigned char KeyNum=0;
    
    if(P3_1==0){KeyNum=1;}
    if(P3_0==0){KeyNum=2;}
    if(P3_2==0){KeyNum=3;}
    if(P3_3==0){KeyNum=4;}
    
    return KeyNum;
}

/**
  * @brief 定时扫描独立按键时的单次执行程序
  * @param  无
  * @retval 无
  */
void Key_Loop(void)
{
    static unsigned char LastKeyNum,NowKeyNum;
    LastKeyNum=NowKeyNum;
    NowKeyNum=Key_GetState();
    if(LastKeyNum && NowKeyNum==0)
    {
        Key_KeyNum=LastKeyNum;
    }
}