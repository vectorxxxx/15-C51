#include <INTRINS.H>

/**
  * @brief 1ms@11.0592MHz
  * @param  xms 毫秒数
  * @retval 无
  */
void Delay(unsigned int xms)
{
	unsigned char data i, j;

	while(xms--)
	{
        _nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}
