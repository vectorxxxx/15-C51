#ifndef __DS1302_H__
#define __DS1302_H__

extern unsigned char DS1302_DateTime[]; // 声明为外部变量

void DS1302_Init();

void DS1302_SetTime();

void DS1302_GetTime();

#endif