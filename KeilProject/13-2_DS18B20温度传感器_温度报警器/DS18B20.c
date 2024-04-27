#include <REGX52.H>
#include "OneWire.h"
#include "LCD1602.h"

// 宏定义DS18B20的ROM指令和功能指令
#define DS18B20_SKIP_ROM            0xCC
#define DS18B20_CONVERT_T           0x44
#define DS18B20_READ_SCRATCHPAD     0xBE

/**
  * @brief 温度变换：初始化→跳过ROM →开始温度变换
  * @param  无
  * @retval 无
  */
void DS18B20_ConvertT(void)
{
    OneWire_Init();                             // 初始化
    OneWire_SendByte(DS18B20_SKIP_ROM);         // 跳过ROM
    OneWire_SendByte(DS18B20_CONVERT_T);        // 开始温度变换
}

/**
  * @brief 温度读取：初始化→跳过ROM →读暂存器→连续的读操作
  * @param  无
  * @retval float 温度，有符号的浮点类型
  */
float DS18B20_ReadT(void)
{
    unsigned char TLSB,TMSB;
    int Temp;
    float T;
    
    OneWire_Init();                             // 初始化
    OneWire_SendByte(DS18B20_SKIP_ROM);         // 跳过ROM
    OneWire_SendByte(DS18B20_READ_SCRATCHPAD);  // 读暂存器
    TLSB=OneWire_ReceiveByte();                 // 连续的读操作
    TMSB=OneWire_ReceiveByte();                 // 连续的读操作
    
    //LCD_ShowBinNum(1,1,TMSB,8);     // 调试用
    //LCD_ShowBinNum(1,9,TLSB,8);     // 调试用
    
    // 温度存储格式：低4位为小数
    // 精度分别为 0.5℃、 0.25℃、 0.125℃、 0.0625℃分辨率
    Temp=TMSB<<8|TLSB;
    T=Temp/16.0;
    return T;
}