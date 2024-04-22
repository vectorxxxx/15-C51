`MatrixLED.h`

```c
#ifndef __MatrixLED_H__
#define __MatrixLED_H__

void MatrixLED_Init();

void MatrixLED_ShowColumn(unsigned char Column, Data);

#endif
```

`MatrixLED.c`

```c
#include <REGX52.H>
#include "Delay.h"

#define MARTIX_LED_PORT P0 // P00~P07
sbit RCK = P3^5; // RCLK
sbit SCK = P3^6; // SRCLK
sbit SER = P3^4; // SER

/**
  * @brief 点阵屏初始化
  * @param  无
  * @retval 无
  */
void MatrixLED_Init()
{
    SCK = 0;
    RCK = 0;
}

/**
  * @brief 向74HC595发送一个字节
  * @param  一个字节
  * @retval 无
  */
void _74HC595_SendByte(unsigned char Byte)
{
    unsigned char i;
    for(i=0;i<8;i++)
    {
        SER = Byte&(0x80>>i);
        SCK = 1;
        SCK = 0;
    }
    RCK = 1;
    RCK = 0;
}

/**
  * @brief LED点阵屏显示一列数据
  * @param  Column 8位段选，从左往右，范围0~7，默认为0
  * @param  Data 8位位选，从上往下，范围0x00~0xFF，1为亮，0为灭
  * @retval 无
  */
void MatrixLED_ShowColumn(unsigned char Column, Data)
{
    // 位选
    _74HC595_SendByte(Data);
    // 段选
    MARTIX_LED_PORT = ~(0x80>>Column);

    // 消影：延时清零
    Delay(1);
    MARTIX_LED_PORT = 0xFF;
}
```

`main.c`

```c
#include <REGX52.H>
#include "MatrixLED.h"
#include "Delay.h"

// 用code修饰表示放入flash中，防止占用ram内存
static const unsigned char code bitmap_bytes[] = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x7F,0x08,0x08,0x08,0x7F,0x00,0x00,0x0E,
    0x15,0x15,0x15,0x0C,0x00,0x00,0x7F,0x01,
    0x02,0x00,0x00,0x7F,0x01,0x02,0x00,0x00,
    0x0E,0x11,0x11,0x0E,0x00,0x00,0x7D,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};


void main()
{
    unsigned char i=0,OffSet=0,Count=0;
    MatrixLED_Init();
    while(1)
    {
        for(i=0;i<8;i++)
        {
            MatrixLED_ShowColumn(i, bitmap_bytes[i+OffSet]);
        }
        if(++Count>10)
        {
            Count=0;
            if (++OffSet>40) OffSet=0;
        }
    }
}
```

