#include <REGX52.H>

// LED引脚定义
sbit LED=P2^0;

/**
  * @brief 简单延时函数
  * @param  t 延时次数
  * @retval 无
  */
void Delay(unsigned char t)
{
    while(t-->0);
}

void main()
{
    unsigned char Total=100,Count=20,t,c;
    while(1)
    {
        // LED灯由暗到亮
        for(t=0;t<Total;t++)
        {
            for(c=0;c<Count;c++)
            {
                LED=0;
                Delay(t);
                LED=1;
                Delay(Total-t);
            }
        }
        // LED灯由亮到暗
        for(t=Total;t>0;t--)
        {
            for(c=0;c<Count;c++)
            {
                LED=0;
                Delay(t);
                LED=1;
                Delay(Total-t);
            }
        }
    }
}
