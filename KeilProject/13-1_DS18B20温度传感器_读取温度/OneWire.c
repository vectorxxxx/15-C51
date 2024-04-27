#include <REGX52.H>

// DS18B02引脚位定义
sbit OneWire_DQ=P3^7;

/**
  * @brief 初始化：
            主机将总线拉低至少480us，然后释放总线，等待15~60us后，存在的从机会拉低总线60~240us以响应主机，之后从机将释放总线
  * @param  无
  * @retval Ack 从机应答
  */
unsigned char OneWire_Init(void)
{
    // data用于定义存储在RAM中的数据；code用于定义存储在ROM中的代码
    // unsigned char data i;
    unsigned char i,Ack;
    OneWire_DQ=1;
    OneWire_DQ=0;
    // 由STCAI-ISP的软件延时计算器生成：系统频率@11.0592MHz，8051指令集STC-Y1
    // 经测试，函数本身调用时间为5us，_nop_()函数调用时间为1us
	i = 227;while (--i);        // (500-6)us
    OneWire_DQ=1;
    i = 29;while (--i);         // (70-6)us
    Ack=OneWire_DQ;
    i = 227;while (--i);        // (500-6)us
    return Ack;
}

/**
  * @brief 发送一位：
            主机将总线拉低60~120us，然后释放总线，表示发送0；主机将总线拉低1~15us，然后释放总线，表示发送1。
            从机将在总线拉低30us后（典型值）读取电平，整个时间片应大于60us
  * @param  Bit 发送的位
  * @retval 无
  */
void OneWire_SendBit(unsigned char Bit)
{
    unsigned char i;    
    OneWire_DQ=0;
    i = 4;while (--i);          // 10us
    OneWire_DQ=Bit;
    i = 23;while (--i);         // 50us
    OneWire_DQ=1;
}

/**
  * @brief 接收一位：
            主机将总线拉低1~15us，然后释放总线，并在拉低后15us内读取总线电平（尽量贴近15us的末尾），
            读取为低电平则为接收0，读取为高电平则为接收1 ，整个时间片应大于60us
  * @param  无
  * @retval Bit 接收的位
  */
unsigned char OneWire_ReceiveBit(void)
{
    unsigned char i,Bit;
    OneWire_DQ=0;
    i = 2;while (--i);          // 5us
    OneWire_DQ=1;
    i = 2;while (--i);          // 5us
    Bit=OneWire_DQ;
    i = 23;while (--i);         // 50us
    return Bit;
}

/**
  * @brief 发送一个字节：连续调用8次发送一位的时序，依次发送一个字节的8位（低位在前）
  * @param  Byte 发送的字节
  * @retval 无
  */
void OneWire_SendByte(unsigned char Byte)
{
    unsigned char i;
    for(i=0;i<8;i++)
    {
        OneWire_SendBit(Byte&(0x01<<i));
    }
}

/**
  * @brief 接收一个字节：连续调用8次接收一位的时序，依次接收一个字节的8位（低位在前）
  * @param  无
  * @retval Byte 接收的字节
  */
unsigned char OneWire_ReceiveByte(void)
{
    unsigned char i,Byte=0x00;
    for(i=0;i<8;i++)
    {
        if(OneWire_ReceiveBit()) Byte|=(0x01<<i);
    }
    return Byte;
}