#ifndef __TIMER0_H__
#define __TIMER0_H__

void Timer0_Init(void);
void Timer0_SetCounter(unsigned int Counter);
unsigned int Timer0_GetCounter();
void Timer0_Run(unsigned char Flag);

#endif