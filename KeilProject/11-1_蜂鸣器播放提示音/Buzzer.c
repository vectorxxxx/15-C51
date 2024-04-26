#include <REGX52.H>
#include <INTRINS.H>

// 蜂鸣器端口位定义
sbit Buzzer=P2^5;  // 五线四项步进电机

/**
  * @brief 蜂鸣器私有延时函数，@11.0592MHz
  * @param  无
  * @retval 无
  */
void Buzzer_Delay500us(void)
{
	unsigned char data i;

	_nop_();
	i = 227;
	while (--i);
}

/**
  * @brief 蜂鸣器按照指定毫秒数鸣叫
  * @param  ms 毫秒数
  * @retval 无
  */
void Buzzer_Beep(unsigned int ms)
{
    unsigned int i;
    for(i=0;i<ms*2;i++)
    {
        Buzzer=!Buzzer;
        Buzzer_Delay500us();
    }
}