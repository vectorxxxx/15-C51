#ifndef __AT24C02_H__
#define __AT24C02_H__
 
void AT24C02_WriteData(unsigned char WordAddress,Data);

unsigned char AT24C02_ReadData(unsigned char WordAddress);

#endif