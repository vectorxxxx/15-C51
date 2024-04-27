#include <REGX52.H>
#include "I2C.h"

// AT24C02的固定地址为1010，可配置地址本开发板上为000
// 所以SLAVE ADDRESS+W为0xA0，SLAVE ADDRESS+R为0xA1
#define AT24C02_ADDRESS_W   0xA0
#define AT24C02_ADDRESS_R   0xA1

/**
  * @brief 发送一帧数据
  * @param  WordAddress 字地址
  * @param  Data 要发送的帧数据
  * @retval 无
  */
void AT24C02_WriteData(unsigned char WordAddress,Data)
{
    I2C_Start();
    I2C_SendByte(AT24C02_ADDRESS_W);
    I2C_ReceiveAck();
    I2C_SendByte(WordAddress);
    I2C_ReceiveAck();
    I2C_SendByte(Data);
    I2C_ReceiveAck();
    I2C_Stop();
}

/**
  * @brief 接收一帧数据
  * @param  WordAddress 字地址
  * @retval Data 接收到的帧数据
  */
unsigned char AT24C02_ReadData(unsigned char WordAddress)
{
    unsigned char Data;
    I2C_Start();
    I2C_SendByte(AT24C02_ADDRESS_W);
    I2C_ReceiveAck();
    I2C_SendByte(WordAddress);
    I2C_ReceiveAck();
    I2C_Start();
    I2C_SendByte(AT24C02_ADDRESS_R);
    I2C_ReceiveAck();
    Data=I2C_ReceiveByte();
    I2C_SendAck(1);
    I2C_Stop();
    return Data;
}