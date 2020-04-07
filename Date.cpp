//
// Created by YHD on 25.02.2020 
//

#include "Date.h"
#include <string>
#include <random>
#include <iostream>

int Date::daysOfMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

Date::Date(const char* p) {
    std::string str(p);
    day = std::stoi(str.substr(0, 2));
    month = std::stoi(str.substr(3, 5));
    year = std::stoi(str.substr(6, 10));
}

Date Date::random_date() {
    static std::mt19937 eng{ std::random_device{}() };
    static std::uniform_int_distribution<int> randomYear{ 1940, 2020 };
    static std::uniform_int_distribution<int> randomMonth{ 1, 12 };
    static std::uniform_int_distribution<int> randomDay{ 1, randomMonth(eng) };

    return Date{ randomDay(eng), randomMonth(eng), randomYear(eng) };
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.day << "/" << date.month << "/" << date.year << "\n";
    return os;
} //31

std::istream& operator>>(std::istream& is, Date& date) {
    is >> date.day >> date.month >> date.year;
    return is;
} //32

std::ostream& operator<<(std::ostream& out, const Date::WeekDay& wDay)
{
    std::string day;

    switch (wDay) {
        case Date::WeekDay(0): day = "Sunday"; break;
        case Date::WeekDay(1): day = "Monday"; break;
        case Date::WeekDay(2): day = "Tuesday"; break;
        case Date::WeekDay(3): day = "Wednesday"; break;
        case Date::WeekDay(4): day = "Thursday"; break;
        case Date::WeekDay(5): day = "Friday"; break;
        case Date::WeekDay(6): day = "Saturday"; break;
    }
    return out << day;
}
