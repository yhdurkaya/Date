//
// Created by YHD on 25.02.2020 
//

#ifndef DATE_H
#define DATE_H

#include <iosfwd>
#include <ctime>

static constexpr int SEC_IN_LEAP_YEAR = 31622400;
static constexpr int SEC_IN_YEAR = 31536000;

static constexpr int SEC_IN_DAY = 86400;

class Date {
private:
    int day;
    int month;
    int year;

    static int daysOfMonth[12];

public:
    static constexpr int year_base = 1900;  //1
    static constexpr int random_min_year = 1940;  //2
    static constexpr int random_max_year = 2020;  //3
    enum class WeekDay { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday }; //4

    Date() {
        day = 01;
        month = 01;
        year = 1900;
    } //5

    explicit Date(int d, int m, int y) : day{ d }, month{ m }, year{ y } {	}//6

    explicit Date(const char* p);  //7

    explicit Date(std::time_t timer) {
        day = 01;
        month = 01;
        year = 1970;

        std::time_t nowSecond = time(0);

        while (nowSecond > SEC_IN_YEAR) {
            if ((year % 4) != 0) {
                nowSecond -= SEC_IN_YEAR;
                year++;
            }
            else if ((year % 4) == 0) {
                nowSecond -= SEC_IN_LEAP_YEAR;
                year++;
            }
        }

        if ((year % 4) != 0) {
            for (size_t i = 0; nowSecond > (daysOfMonth[i] * SEC_IN_DAY); i++) {
                nowSecond -= daysOfMonth[i] * SEC_IN_DAY;
                month++;
            }

            while (nowSecond > SEC_IN_DAY) {
                nowSecond -= SEC_IN_DAY;
                day++;
            }
        }

        if ((year % 4) == 0) {
            for (size_t i = 0; nowSecond > (daysOfMonth[i] * SEC_IN_DAY); i++) {
                if (i == 1) {
                    nowSecond -= (daysOfMonth[i] + 1) * SEC_IN_DAY;
                    month++;
                }
                else {
                    nowSecond -= daysOfMonth[i] * SEC_IN_DAY;
                    month++;
                }
            }

            while (nowSecond > SEC_IN_DAY) {
                nowSecond -= SEC_IN_DAY;
                day++;
            }
        }
    } //8

    int get_month_day()const {
        return day;
    } //9

    int get_month()const {
        return month;
    } //10

    int get_year()const {
        return year;
    } //11

    int get_year_day()const {
        int dayOfYear = 0;

        for (size_t i = 1; i < get_month(); ++i) {
            dayOfYear += daysOfMonth[i - 1];
        }
        dayOfYear += get_month_day();

        return dayOfYear;
    } //12

    WeekDay get_week_day()const {
        int total_day = 0;
        int yearTemp = 1900;
        WeekDay wDay;
        while (yearTemp < year) {
            if (yearTemp % 4 == 0) {
                total_day += 366;
            }
            else {
                total_day += 365;
            }
            yearTemp++;
        }
        total_day += get_year_day();

        wDay = static_cast<WeekDay>((total_day) % 7);
        return wDay;
    } //13

    Date& set_month_day(int day) {
        this->day = day;
        return *this;
    } //14

    Date& set_month(int month) {
        this->month = month;
        return *this;
    } //15

    Date& set_year(int year) {
        this->year = year;
        return *this;
    } //16

    Date& set(int day, int mon, int year) {
        this->day = day;
        this->month = month;
        this->year = year;
        return *this;
    } //17

    Date operator-(int day)const {
        Date test = *this;
        while (day) {
            --test;
            day--;
        }
        return test;
    } //18

    Date& operator+=(int day) {
        while (day) {
            ++(*this);
            day--;
        }
        return *this;
    }//19

    Date& operator-=(int day) {
        while (day) {
            --(*this);
            day--;
        }
        return *this;
    } //20

    Date& operator++() {
        if (this->day == daysOfMonth[this->month - 1]) {
            this->day = 1;
            if (this->month == 12) {
                this->year++;
                this->month = 1;
            }
            else {
                this->month++;
            }
        }
        else {
            this->day++;
        }
        return *this;
    } //21

    Date operator++(int) {
        Date temp{ *this };
        ++(*this);
        return temp;

    } //22

    Date& operator--() {
        this->day--;
        if (this->day == 0) {
            this->month--;
            this->day = daysOfMonth[this->month - 1];
            if (this->month == 0) {
                this->year--;
                this->month = 12;
                this->day = 31;
            }
        }
        return *this;
    } //23

    Date operator--(int) {
        Date temp{ *this };
        --(*this);
        return temp;
    } //24

    static Date random_date(); //25

    static constexpr bool isleap(int y) {
        return (y % 4) == 0;
    } //26

    friend bool operator<(const Date& date1, const Date& date2) {
        if (date1.year == date2.year) {
            if (date1.month == date2.month) {
                return (date1.day < date2.day);
            }
            return (date1.month < date2.month);
        }
        return (date1.year < date2.year);
    } //27

    friend bool operator==(const Date& date1, const Date& date2) {
        if (date1.day == date2.day) {
            if (date1.month == date2.month) {
                return date1.day == date2.day;
            }
            return false;
        }
        return false;
    } //27

    friend std::ostream& operator<<(std::ostream& os, const Date& date);
    friend std::istream& operator>>(std::istream& is, Date& date);
};

inline bool operator<=(const Date& date1, const Date& date2) {
    return !(date2 < date1);
} //27

inline bool operator>(const Date& date1, const Date& date2) {
    return (date2 < date1);
}  //27

inline bool operator>=(const Date& date1, const Date& date2) {
    return !(date1 < date2);
} //27

inline bool operator!=(const Date& date1, const Date& date2) {
    return !(date1 == date2);
} //27

inline int operator-(const Date& d1, const Date& d2) {
    int difference = 365 * (d1.get_year() - d2.get_year());
    difference += d1.get_year_day() - d2.get_year_day();
    return difference;
}//28

inline Date operator+(const Date& date, int n) {
    Date newDate(date);
    newDate += n;
    return newDate;
} //29

inline Date operator+(int n, const Date& date) {
    Date newDate(date);
    newDate += n;
    return newDate;
} //29


inline Date::WeekDay& operator++(Date::WeekDay& r){
    auto wDay = static_cast<int>(r);
    ++wDay %= 7;
    return r = static_cast<Date::WeekDay>(wDay);
}//30

inline Date::WeekDay operator++(Date::WeekDay& r, int ) {
    Date::WeekDay result{ r };
    ++r;
    return result;
} //30

inline Date::WeekDay& operator--(Date::WeekDay& r) {
    auto wDay = static_cast<int>(r);
    --wDay %= 7;
    return r = static_cast<Date::WeekDay>(wDay);
}//30

inline Date::WeekDay operator--(Date::WeekDay& r, int ) {
    Date::WeekDay result{ r };
    --r;
    return result;
} //30


std::ostream& operator<<(std::ostream& out, const Date::WeekDay& wDay);

#endif
