#include <REGX52.H>
#include "Delay.h"

unsigned char NixieBuf[9] = {0,10,10,10,10,10,10,10,10};

unsigned char NixieTable[] = {
	0x3f,   // 0
	0x06,   // 1
	0x5b,   // 2
	0x4f,   // 3
	0x66,   // 4
	0x6d,   // 5
	0x7d,   // 6
	0x07,   // 7
	0x7f,   // 8
	0x6f,   // 9
    0x40    // -
};

/**
  * @brief 数码管显示数字
  * @param  Location 显示第几个数码管
  * @param  Number 显示的数字，0~9 或 -
  * @retval 无
  */
void Nixie(unsigned char Location, Number)
{
    NixieBuf[Location]=Number;
}

/**
  * @brief 扫描数码管
  * @param  Location 显示第几个数码管
  * @param  Number 显示数字，0~9 或 -
  * @retval 无
  */
void Nixie_Scan(unsigned char Location, Number)
{
    // 先清零
	P=0x00;
    
    // 段选
	switch(Location)
	{
		case 1: P2_4=1; P2_3=1; P2_2=1; break;
		case 2: P2_4=1; P2_3=1; P2_2=0; break;
		case 3: P2_4=1; P2_3=0; P2_2=1; break;
		case 4: P2_4=1; P2_3=0; P2_2=0; break;
		case 5: P2_4=0; P2_3=1; P2_2=1; break;
		case 6: P2_4=0; P2_3=1; P2_2=0; break;
		case 7: P2_4=0; P2_3=0; P2_2=1; break;
		case 8: P2_4=0; P2_3=0; P2_2=0; break;
		default: break;
	}

    // 位选
	P0=NixieTable[Number];
}

/**
  * @brief 定时扫描数码管时的单次执行程序
  * @param  无
  * @retval 无
  */
void Nixie_Loop(void)
{
    static unsigned char i=1;
    Nixie_Scan(i, NixieBuf[i]);
    if(++i>=9)i=0;
}