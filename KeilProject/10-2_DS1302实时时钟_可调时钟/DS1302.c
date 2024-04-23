#include <REGX52.H>

// 定义寄存器位
sbit DS1302_SCLK = P3^6;    // Serial Clock
sbit DS1302_IO = P3^4;      // Input/Output
sbit DS1302_CE = P3^5;      // Chip Enable


// 重定义命令字寄存器地址（定义的为Write命令字，Read命令字需要进1位）
#define DS1302_SECOND       0x80
#define DS1302_MINUTE       0x82
#define DS1302_HOUR         0x84
#define DS1302_DATE         0x86
#define DS1302_MONTH        0x88
#define DS1302_DAY          0x8A
#define DS1302_YEAR         0x8C
#define DS1302_WP           0x8E


// 命令字数组
unsigned char DS1302_Register[] = {
    DS1302_YEAR,DS1302_MONTH,DS1302_DATE,
    DS1302_HOUR,DS1302_MINUTE,DS1302_SECOND,
    DS1302_DAY
}; // 年-月-日 时:分:秒 星期


// 日期时间数组
char DS1302_DateTime[] = {
    24,4,22,
    22,50,55,
    1
}; // 年-月-日 时:分:秒 星期


/**
  * @brief DS1302时钟初始化
  * @param  无
  * @retval 无
  */
void DS1302_Init()
{
    DS1302_CE = 0;
    DS1302_SCLK = 0;
}


/**
  * @brief 写入命令字和一个字节的数据
  * @param  Command 命令字
  * @param  Data 数据
  * @retval 无
  */
void DS1302_WriteByte(unsigned char Command, Data)
{
    unsigned char i;
    DS1302_CE = 1;

    // 命令字
    for(i=0;i<8;i++)
    {
        DS1302_IO=Command&(0x01<<i);
        DS1302_SCLK=1;
        DS1302_SCLK=0;
    }
    // 数据
    for(i=0;i<8;i++)
    {
        DS1302_IO=Data&(0x01<<i);
        DS1302_SCLK=1;
        DS1302_SCLK=0;
    }
    
    DS1302_CE = 0;
}


/**
  * @brief 根据命令字读取对应数据
  * @param  Command 命令字
  * @retval 数据
  */
unsigned char DS1302_ReadByte(unsigned char Command)
{
    unsigned char i,Data=0x00;
    Command|=0x01; // 定义的为Write命令字，Read命令字需要进1位
    DS1302_CE = 1;
    
    // 命令字
    for(i=0;i<8;i++)
    {
        DS1302_IO=Command&(0x01<<i);
        DS1302_SCLK=0;
        DS1302_SCLK=1;
    }
    // 数据
    for(i=0;i<8;i++)
    {
        DS1302_SCLK=1;
        DS1302_SCLK=0;
        if(DS1302_IO) Data|=(0x01<<i);
    }
    
    DS1302_CE = 0;
    DS1302_IO = 0;
    return Data;
}


/**
  * @brief 十进制转BCD码
  * @param  无
  * @retval 无
  */
unsigned char DS1302_DEC2BCD(unsigned char DEC)
{
    return DEC/10*16+DEC%10;
}


/**
  * @brief BCD码转十进制
  * @param  无
  * @retval 无
  */
unsigned char DS1302_BCD2DEC(unsigned char BCD)
{
    return BCD/16*10+BCD%16;
}


/**
  * @brief 设置日期时间
  * @param  无
  * @retval 无
  */
void DS1302_SetDateTime(void)
{
    unsigned char i;
    
    // 解除写保护
    DS1302_WriteByte(DS1302_WP, 0x00);
    
    // 写入日期时间
    for(i=0;i<7;i++)
    {
        DS1302_WriteByte(
            DS1302_Register[i], 
            DS1302_DEC2BCD(DS1302_DateTime[i])
        );
    }
    
    // 恢复写保护
    DS1302_WriteByte(DS1302_WP, 0x80);
}


/**
  * @brief 获取日期时间
  * @param  无
  * @retval 无
  */
void DS1302_GetDateTime(void)
{
    unsigned char i;
    for(i=0;i<7;i++)
    {
        DS1302_DateTime[i]=DS1302_BCD2DEC(
            DS1302_ReadByte(DS1302_Register[i])
        );
    }
}