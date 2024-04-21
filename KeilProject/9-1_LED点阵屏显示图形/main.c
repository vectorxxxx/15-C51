#include <REGX52.H>
#include "MatrixLED.h"
#include "Delay.h"

unsigned char Datas1[] = {0x38,0x7C,0x7E,0x3F,0x3F,0x7E,0x7C,0x38}; // 爱心
unsigned char Datas2[] = {0x3C,0x52,0xD3,0x46,0x46,0xD3,0x52,0x3C}; // bilibili

void main()
{
    MatrixLED_Init();
    while(1)
    {
        int i,j;
//        for(i=0;i<8;i++)
//        {
//            MatrixLED_ShowColumn(i, Datas1[i]);
//        } 
        for(j=0;j<8;j++)
        {
            MatrixLED_ShowColumn(j, Datas2[j]);
        }

    }
}
