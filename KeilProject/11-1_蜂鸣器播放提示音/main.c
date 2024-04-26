#include <REGX52.H>
#include "Key.h"
#include "Nixie.h"
#include "Buzzer.h"

unsigned char KeyNum;

void main()
{
    Nixie(1,0);
    while(1)
    {
        KeyNum=Key();
        if(KeyNum)
        {
            Nixie(1,KeyNum);
            Buzzer_Beep(KeyNum*100);
        }
    }
}
