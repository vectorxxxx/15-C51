#include <STC89C5xRC.H>
#include "Delay.h"
#include "UART.h"

void main()
{
    UART_Init();
    while(1)
    {

    }
}

/**
  * @brief 串口中断子函数
  * @param  无
  * @retval 无
  */
void UART_Routine(void)     interrupt 4
{
    if(RI==1)
    {
        P2=~SBUF;
        UART_SendByte(SBUF);
        
        RI=0;
    }
}