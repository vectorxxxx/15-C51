#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"
#include "MatrixKey.h"
#include "Tip.h"
#include "PassWord.h"

unsigned char KeyNum;
unsigned int PassWord,Count;
unsigned int CorrectPassWord=1234;

// 输入密码
void InputPassWord()
{
    if(Count>=4) return;
    Count++;
    
    PassWord=PassWord*10+KeyNum%10;
    ShowPassWord(PassWord);
    
    ShowNth();
}

// 确认密码
void ConfirmPassWord()
{
    if(PassWord==CorrectPassWord) ShowOK();
    else ShowERR();
    
    Count=0;
    
    PassWord=0;
    ShowPassWord(PassWord);
}

// 重置密码
void ResetPassWord()
{
    Count=0;
    
    PassWord=0;
    ShowPassWord(PassWord);
    
    ShowNth();
}

// 撤销密码
void BackPassWord()
{
    if(Count<=0) return;
    Count--;
    
    PassWord=PassWord/10;
    ShowPassWord(PassWord);
    
    ShowNth();
}

void PassWordLock(){
    KeyNum=MatrixKey();
    if(!KeyNum) return;
    
    if(KeyNum<=10) InputPassWord();
    else if(KeyNum==11) ConfirmPassWord();
    else if(KeyNum==12) ResetPassWord();
    else if(KeyNum==13) BackPassWord();
}

void main()
{
    LCD_Init();
    LCD_ShowString(1,1,"PassWord:");
	while(1)
	{
        PassWordLock();
	}
}