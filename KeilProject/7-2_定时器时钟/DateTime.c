unsigned int days[]= {31,29,31,30,31,30,31,31,30,31,30,31};

/**
  * @brief 获取二月天数
  * @param  无
  * @retval 无
  */
unsigned int GetFebruaryDay(unsigned int year)
{
    // 大闰年
    if(year%400 == 0)
        return 29;
    // 小闰年
    else if(year%4 == 0 && year%100 != 0) 
        return 29;
    // 非闰年
    else 
        return 28;
}

/**
  * @brief 获取某月天数
  * @param  无
  * @retval 无
  */
unsigned int GetDay(unsigned int year, unsigned int month)
{
    unsigned int day = days[month-1];
    if(month == 2) 
        GetFebruaryDay(year);
    return day;
}