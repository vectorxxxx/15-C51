#include <REGX52.H>
#include "Delay.h"

// 定义XPT2046引脚
sbit XPT2046_CS=P3^5;
sbit XPT2046_DCLK=P3^6;
sbit XPT2046_DIN=P3^4;
sbit XPT2046_DOUT=P3^7;

/**
  * @brief 读取AD数值
  * @param  Command     命令字 
  * @param  Resolution  分辨率，为 8 选择 8 位为转换分辨率，为 12 选择 12 位分辨率
  * @retval ADValue     AD值，8 位为 0~255，12 位为 0~4095
  */
unsigned int XPT2046_ReadAD(unsigned char Command,unsigned char Resolution)
{
    unsigned char i;
    unsigned int ADValue=0;
    
    // 12 位分辨率
    if(Resolution==12){Command&=0xF4;}
    
    XPT2046_DCLK=0;
    XPT2046_CS=0;
    for(i=0;i<8;i++)
    {
        XPT2046_DIN=Command&(0x80>>i);
        XPT2046_DCLK=1;
        XPT2046_DCLK=0;
    }
    for(i=0;i<16;i++)
    {
        XPT2046_DCLK=1;
        XPT2046_DCLK=0;
        if(XPT2046_DOUT){ADValue|=(0x8000>>i);};
        Delay(1);
    }
    XPT2046_CS=1;
    
    if(Resolution==12) return ADValue>>4;
    else return ADValue>>8;
}