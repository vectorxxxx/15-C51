#include <REG52.H>

/**
 * @brief 定时器0初始化，1毫秒@11.0592MHz
 * @param  无
 * @retval 无
 */
void Timer0_Init(void)
{
    // 1、设置定时器/计数器工作模式寄存器TMOD
    //      0 1   16位定时器/计数器，TL0、TH0全用
    TMOD &= 0xF0; // 高4位不变，低4位清零
    TMOD |= 0x01; // 高4位不变，低4位置一

    // 2、设置定时器0初始值
    TL0 = 0; // Timer Low  0（8bit）
    TH0 = 0; // Timer High 0（8bit）

    // 3、定时器/计数器0控制寄存器TCON
    TF0 = 0; // 定时器0溢出中断标志置0
    TR0 = 0; // 定时器0的运行控制位置0
}

/**
  * @brief 设置计数
  * @param  Counter 计数器范围，0~65535
  * @retval 无
  */
void Timer0_SetCounter(unsigned int Counter)
{
    TL0=Counter%256;
    TH0=Counter/256;
}

/**
  * @brief 获取计数
  * @param  无
  * @retval Counter 计数器范围，0~65535
  */
unsigned int Timer0_GetCounter()
{
    return (TH0<<8)|TL0;
}

/**
  * @brief 控制运行定时器0
  * @param  无
  * @retval 无
  */
void Timer0_Run(unsigned char Flag)
{
    TR0 = Flag;
}