#include <REGX52.H>
#include "Delay.h"
#include "Nixie.h"

void main()
{
	while(1)
	{
		# LED灯闪烁
//		P2_0=1;
//		Delay(500);
//		P2_0=0;
//		Delay(500);
		
		# 动态数码管
		Nixie(1,1);
		Nixie(2,2);
		Nixie(3,3);
		Nixie(4,4);
		Nixie(5,5);
		Nixie(6,6);
		Nixie(7,7);
		Nixie(8,8);
	}
}