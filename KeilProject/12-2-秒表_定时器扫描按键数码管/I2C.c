#include <REGX52.H>

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

/**
  * @brief I2C起始条件：ISCL高电平期间，SDA从高电平切换到低电平
  * @param  无
  * @retval 无
  */
void I2C_Start()
{
    I2C_SDA=1;
    I2C_SCL=1;
    I2C_SDA=0;
    I2C_SCL=0;
}

/**
  * @brief I2C终止条件：SCL高电平期间，SDA从低电平切换到高电平
  * @param  无
  * @retval 无
  */
void I2C_Stop()
{
    I2C_SDA=0;
    I2C_SCL=1;
    I2C_SDA=1;
}

/**
  * @brief 发送一个字节：SCL低电平期间，
                主机将数据位依次放到SDA线上（高位在前），然后拉高SCL，
                从机将在SCL高电平期间读取数据位，所以SCL高电平期间SDA不允许有数据变化，
                依次循环上述过程8次，即可发送一个字节
  * @param  无
  * @retval 无
  */
void I2C_SendByte(unsigned char Byte)
{
    unsigned char i;   
    for(i=0;i<8;i++)
    {
        I2C_SDA=Byte&(0x80>>i);
        I2C_SCL=1;
        I2C_SCL=0;
    }
}

/**
  * @brief 接收一个字节：SCL低电平期间，
                从机将数据位依次放到SDA线上（高位在前），然后拉高SCL，
                主机将在SCL高电平期间读取数据位，所以SCL高电平期间SDA不允许有数据变化，
                依次循环上述过程8次，即可接收一个字节
  * @param  无
  * @retval 无
  */
unsigned char I2C_ReceiveByte()
{
    unsigned char i,Byte=0x00;
    // 主机在接收之前，需要释放SDA
    I2C_SDA=1;
    for(i=0;i<8;i++)
    {
        I2C_SCL=1;
        if(I2C_SDA){Byte|=(0x80>>i);}
        I2C_SCL=0;
    }
    return Byte;
}

/**
  * @brief 发送应答：在接收完一个字节之后，主机在下一个时钟发送一位数据
  * @param  AckBit 数据0表示应答，数据1表示非应答
  * @retval 无
  */
void I2C_SendAck(unsigned char AckBit)
{
    I2C_SDA=AckBit;
    I2C_SCL=1;
    I2C_SCL=0;
}

/**
  * @brief 接收应答：在发送完一个字节之后，主机在下一个时钟接收一位数据，判断从机是否应答，
  * @param  数据0表示应答，数据1表示非应答
  * @retval 无
  */
unsigned char I2C_ReceiveAck()
{
    unsigned char AckBit;
    // 主机在接收之前，需要释放SDA
    I2C_SDA=1;
    I2C_SCL=1;
    AckBit=I2C_SDA;
    I2C_SCL=0;
    return AckBit;
}