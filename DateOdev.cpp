//
// Created by YHD on 25.02.2020 
//

#include "Date.h"
#include <iostream>
#include <ctime>


int main()
{
    std::time_t time = 0;

    Date today(time);
    Date birth("08/03/1994");
    /*
    std::cout << today.get_month_day() << "." << today.get_month() << "." <<
        today.get_year() << "	" << today.get_year_day() << std::endl;
    std::cout << tomorrow.get_month_day() << "." << tomorrow.get_month() << "." <<
        tomorrow.get_year() << "	" << tomorrow.get_year_day() << std::endl;

    std::cout << today.get_month_day() << "." << today.get_month() << "." <<
        today.get_year() << "	" << today.get_year_day() << std::endl;

    today = Date::random_date();

    std::cout << today.get_month_day() << "." << today.get_month() << "." <<
        today.get_year() << "	" << today.get_year_day() << std::endl;

    std::cout << Date::isleap(2012) << std::endl;
    std::cout << Date::isleap(2013) << std::endl;

    std::cout << (today < tomorrow) << std::endl;
    std::cout << (today <= tomorrow) << std::endl;
    std::cout << (today > tomorrow) << std::endl;
    std::cout << (today >= tomorrow) << std::endl;
    std::cout << (today == tomorrow) << std::endl;
    std::cout << (today != tomorrow) << std::endl;

    std::cout << (today - tomorrow) << std::endl;
    */

    std::cout << today << std::endl;
    std::cout << birth << std::endl;
    std::cout << today.get_week_day() << std::endl;
    
    today++;
    auto weekdayTemp = today.get_week_day();
    ++weekdayTemp;
    std::cout << weekdayTemp << std::endl;

}
