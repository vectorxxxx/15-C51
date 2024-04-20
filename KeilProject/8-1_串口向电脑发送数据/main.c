#include <STC89C5xRC.H>
#include "Delay.h"
#include "UART.h"

unsigned int Sec;

void main()
{
    UART_Init();
    while(1)
    {
        UART_SendByte(Sec++);
        Delay(1000);
    }
}
