#include "dbmsLib5.h"
#include <string>
#include <strstream>


const int DBDate5::arrDays[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

DBDate5::DBDate5(string date)
{
    int d = stoi(date.substr(0, date.find_first_of(".")));
    int m = stoi(date.substr(date.find_first_of(".") + 1, date.find_last_of(".")));
    int y = stoi(date.substr(date.find_last_of(".") + 1));

    if (y > 0 && y < 10000 && m > 0 && m < 13 && d > 0 && d <= GetDaysInMonth(m, y)) {
        day = d;
        month = m;
        year = y;
    }
    else {
        cout << "Недопустимая дата! Установлена 1.1.1\n";
        day = 1;
        month = 1;
        year = 1;
    }
}

DBDate5::DBDate5(int d, int m, int y)
{
    if (y > 0 && y < 10000 && m > 0 && m < 13 && d > 0 && d <= GetDaysInMonth(m, y)) {
        day = d;
        month = m;
        year = y;
    }
    else {
        cout << "Недопустимая дата! Установлена 1.1.1\n";
        day = 1;
        month = 1;
        year = 1;
    }
}

bool DBDate5::IsLeapYear(int year)
{
    if (year % 400 == 0) {
        return true;
    }
    return ((year % 4 == 0) && (year % 100 != 0));
}

int DBDate5::GetDay() { return day; }
int DBDate5::GetMonth() { return month; }
int DBDate5::GetYear() { return year; }

int DBDate5::GetDaysInMonth(int month, int year)
{
    int days_in_month = arrDays[month];
    if (IsLeapYear(year) && month == 2)
        days_in_month += 1;
    return days_in_month;
}

int DBDate5::DaysInCurYear()
{
    int days = 0;
    for (int i = 1; i < month; ++i) {
        if (i == 2 && IsLeapYear(year))
            days += 1;
        days += arrDays[i];
    }
    days += day;
    return days;
}

bool DBDate5::operator==(const DBDate5& date)
{
    return (day == date.day && month == date.month && year == date.year);
}
bool DBDate5::operator<(const DBDate5& date)
{
    if (year != date.year) {
        return year < date.year;
    }
    else

    {
        if (month != date.month) {
            return month < date.month;
        }
        else {
            if (day != date.day) {
                return day < date.month;
            }
            else {
                return false;
            }
        }
    }
}
bool DBDate5::operator>(const DBDate5& date)
{
    if (year != date.year) {
        return year > date.year;
    }
    else
    {
        if (month != date.month) {
            return month > date.month;
        }
        else {
            if (day != date.day) {
                return day > date.month;
            }
            else {
                return false;
            }
        }
    }
}
bool DBDate5::operator<=(const DBDate5& date)
{
    return !(*this > date);
}
bool DBDate5::operator>=(const DBDate5& date)
{
    return !(*this < date);
}
bool DBDate5::operator!=(const DBDate5& date)
{
    return !(*this == date);
}

string DateToStr(const DBDate5& date)
{
    char buffer[12];
    strstream stream(buffer, 12);
    stream << date.day << "." << date.month << "." << date.year << '\0';
    return buffer;
}

ostream& operator<<(ostream& out, DBDate5& date)
{
    return out << DateToStr(date);
}

int DBDate5::GetJDN()
{
    int a = (14 - GetMonth()) / 12;
    int y = GetYear() + 4800 - a;
    int m = GetMonth() + 12 * a - 3;
    int jdn = GetDay() + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
    return jdn;
}

DBDate5 DBDate5::GetDateFromJDN(int jdn)
{
    int a = jdn + 32044;
    int b = (4 * a + 3) / 146097;
    int c = a - (146097 * b) / 4;
    int d = (4 * c + 3) / 1461;
    int e = c - (1461 * d) / 4;
    int m = (5 * e + 2) / 153;
    int day = e - (153 * m + 2) / 5 + 1;
    int month = m + 3 - 12 * (m / 10);
    int year = 100 * b + d - 4800 + (m / 10);
    DBDate5 ret(day, month, year);
    return ret;
}

DBDate5& DBDate5::operator+=(int days)
{
    *this = GetDateFromJDN(GetJDN() + days);
    return *this;
}

DBDate5& DBDate5::operator-=(int days)
{
    *this = GetDateFromJDN(GetJDN() - days);
    return *this;
}

int DBDate5::operator-(DBDate5& date)
{
    return date.GetJDN() - GetJDN();
}
