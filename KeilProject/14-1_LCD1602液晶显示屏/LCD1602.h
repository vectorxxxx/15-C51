#ifndef __LCD1602_H__
#define __LCD1602_H__

void LCD1602_Init(void);
void LCD1602_ShowChar(unsigned char Line,unsigned char Column,unsigned char Char);
void LCD1602_ShowStr(unsigned char Line,unsigned char Column,unsigned char *Str);
void LCD1602_ShowNum(unsigned char Line,unsigned char Column,unsigned int Num,unsigned char Length);
void LCD1602_ShowSignedNum(unsigned char Line,unsigned char Column,int Num,unsigned char Length);
void LCD1602_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Num,unsigned char Length);
void LCD1602_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Num,unsigned char Length);

#endif