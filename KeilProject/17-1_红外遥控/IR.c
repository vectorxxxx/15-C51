#include <REGX52.H>
#include "Timer0.h"
#include "Int0.h"

// 定义变量
unsigned int IR_Time;          // 下降沿间隔时间
unsigned char IR_State;         // 状态机状态

unsigned char IR_Data[4];       // Data数据临时存储
unsigned char IR_pData;         // Data数据指针

unsigned char IR_DataFlag;      // Data状态
unsigned char IR_RepeatFlag;    // Repeat状态

unsigned char IR_Address;       // 地址码
unsigned char IR_Command;       // 命令码

/**
  * @brief 红外遥控初始化
  * @param  无
  * @retval 无
  */
void IR_Init(void)
{
    Timer0_Init();
    Int0_Init();
}

/**
  * @brief 获取红外接收器收到的数据帧标志位
  * @param  无
  * @retval 是否收到数据帧，1为收到，0为未收到
  */
unsigned char IR_GetDataFlag(void)
{
    unsigned char Tmp=IR_DataFlag;
    if(IR_DataFlag)IR_DataFlag=0;
    return Tmp;
}

/**
  * @brief 获取红外接收器收到的连发帧标志位
  * @param  无
  * @retval 是否收到连发帧，1为收到，0为未收到
  */
unsigned char IR_GetRepeatFlag(void)
{
    unsigned char Tmp=IR_RepeatFlag;
    if(IR_RepeatFlag)IR_RepeatFlag=0;
    return Tmp;
}

/**
  * @brief 获取红外接收器收到的地址码
  * @param  无
  * @retval 收到的地址码
  */
unsigned char IR_GetAddress(void)
{
    return IR_Address;
}

/**
  * @brief 红外遥控获取收到的命令码
  * @param  无
  * @retval 收到的命令码
  */
unsigned char IR_GetCommand(void)
{
    return IR_Command;
}

/**
  * @brief 初始化准备
  * @param  无
  * @retval 无
  */
void IR_Prepare(void)
{
    Timer0_SetCounter(0);
    Timer0_Run(1);
    IR_State=1;
}

/**
  * @brief 开始/重复标记
  * @param  无
  * @retval 无
  */
void IR_StartRepeat(void)
{
    IR_Time=Timer0_GetCounter();
    Timer0_SetCounter(0);  // 获取到下降沿之间的间隔时间后立即清零，以便对下个下降沿之间的间隔时间进行计时
    
    // Start信号：低电平9ms+高电平4.5ms（判定值在 12MHz 晶振下为 13500，在 11.0592MHz 晶振下为 12442）
    if(IR_Time>13500*(11.0592/12)-500 && IR_Time<13500*(11.0592/12)+500)
    {
        IR_State=2;
    }
    // Repeat信号：低电平9ms+高电平2.25ms（判定值在 12MHz 晶振下为 11250，在 11.0592MHz 晶振下为 10368）
    else if(IR_Time>11250*(11.0592/12)-500 && IR_Time<11250*(11.0592/12)+500)
    {
        IR_RepeatFlag=1;
        // 重复指令无需进行后续的读取数据操作，直接从上一次数据中读取
        // 停止定时器，并将状态置为初始状态，等待下一次外部中断重新开始
        Timer0_Run(0);
        IR_State=0; 
    }
    else 
    {
        IR_State=1; 
    }

}

/**
  * @brief 读取数据
  * @param  无
  * @retval 无
  */
void IR_ReadData(void)
{
    IR_Time=Timer0_GetCounter();
    Timer0_SetCounter(0);
    
    // 逻辑0：低电平560us+高电平560us
    if(IR_Time>1120*(11.0592/12)-500 && IR_Time<1120*(11.0592/12)+500)
    {
        IR_Data[IR_pData/8]&=~(0x01<<(IR_pData%8)); // 指针所指位置0
        IR_pData++;
    }
    // 逻辑1：低电平560us+高电平1690us
    else if(IR_Time>2250*(11.0592/12)-500 && IR_Time<2250*(11.0592/12)+500)
    {
        IR_Data[IR_pData/8]|=0x01<<(IR_pData%8);    // 指针所指位置1
        IR_pData++;
    }
    else 
    {
        IR_pData=0;                                 // 指针重置
        IR_State=1;                                 // 数据读取有误，回归Start/Repeat状态
    }
    
    // 读取32位数据后，进行反码校验
    if(IR_pData>=32)
    {
        IR_pData=0;
        if(IR_Data[0]==~IR_Data[1] && IR_Data[2]==~IR_Data[3])
        {
            IR_Address=IR_Data[0];
            IR_Command=IR_Data[2];
            IR_DataFlag=1;
        }
        // 任务结束，关闭定时器，并重置状态
        Timer0_Run(0);
        IR_State=0; 
    }
}

/**
  * @brief 外部中断0终端执行程序
  * @param  无
  * @retval 无
  */
void Int0_Routine(void)     interrupt 0
{
    // 0——空闲状态
    if(IR_State==0)
    {
        IR_Prepare();
    }
    // 1——Start/Repeat状态
    else if(IR_State==1)
    {
        IR_StartRepeat();
    }
    // 2——Data状态
    else if(IR_State==2)
    {
        IR_ReadData();
    }
}