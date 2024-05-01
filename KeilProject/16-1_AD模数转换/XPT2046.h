#ifndef __XPT2046_H__
#define __XPT2046_H__

// 宏定义命令字
// 7        S           开始位。为 1 表示一个新的控制字节到来，为 0 则忽略 PIN 引脚上数据
// 6-4      A2-A0       通道选择位。参见表 1 和表 2
//            A2 A1 A0 VBAT   AUXIN   TEMP        YN      XP      YP
//            0  0  0                 +IN(TEMP0)
//            0  0  1                                     +IN
//            0  1  0  +IN
//            0  1  1                                     +IN
//            1  0  0                             +IN
//            1  0  1                                             +IN
//            1  1  0         +IN
//            1  1  1                 +IN(TEMP1)
// 3        MODE        12 位/ 8 位转换分辨率选择位。为 1 选择 8 位为转换分辨率，为 0 选择 12 位分辨率
// 2        SER/DFR     单端输入方式/ 差分输入方式选择位。为 1 是单端输入方式，为 0 是差分输入方式
// 1-0      PD1-PD0     低功率模式选择位。若为 11，器件总处于供电状态;若为 00，器件在变换之间处于低功率模式
//            PD1 PD0 PENIRQ    功能说明
//            0   0   使能      在两次 A／D 转换之间掉电，下次转换一开始，芯片立即进入完全上电状态，而无需额外的延时。在这种模式下，YN 开关一直处于 ON 状态
//            0   1   禁止      参考电压关闭， ADC 打开
//            1   0   使能      参考电压打开， ADC 关闭
//            1   1   禁止      芯片处于上电状态，参考电压和 ADC 总是打开
#define XPT2046_XP      0x9C
#define XPT2046_YP      0xDC
#define XPT2046_VBAT    0xAC
#define XPT2046_AUX     0xEC

unsigned int XPT2046_ReadAD(unsigned char Command,unsigned char Resolution);

#endif