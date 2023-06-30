#include "Lab42_8.h"
#include <iostream>
#include <string>
#include <strstream>
#include <ostream>
using namespace dbmsLib8;



DBDate8::DBDate8(string date) {
    int i = 0;
    string t = "";

    while (date[i] != '.') {
        t += date[i];
        i += 1;
    }
    day = stoi(t);
    i += 1; t = "";
    while (date[i] != '.') {
        t += date[i];
        i += 1;
    }
    month = stoi(t);
    i += 1; t = "";
    while (i < size(date)) {
        t += date[i];
        i += 1;
    }
    year = stoi(t);

    if (!((day >= 1) && (day <= this->GetDaysInMonth(month, year)) && (month >= 1) && (month <= 12))) {
        day = 1; month = 1; year = 1;
    }
}

DBDate8::DBDate8(int d, int m, int y) {
    day = d;
    month = m;
    year = y;
    if (!((day >= 1) && (day <= this->GetDaysInMonth(month, year)) && (month >= 1) && (month <= 12))) {
        day = 1; month = 1; year = 1;
    }
}

string DateToStr8(DBDate8& date) {
    return to_string(date.GetDay()) + "." + to_string(date.GetMonth()) + "." + to_string(date.GetYear());
}

/*
bool DBDate8::IsCorrectDate(int d, int m, int y) {
    return (d >= 1) && (d <= this->GetDaysInMonth(m, y)) && (m >= 1) && (m <= 12);
}
*/
int DBDate8::GetDay() {
    return day;
}

int DBDate8::GetMonth() {
    return month;
}

int DBDate8::GetYear() {
    return year;
}

void DBDate8::SetDay(int d) {
    day = d;
}

void DBDate8::SetYear(int y) {
    year = y;
}

void DBDate8::SetMonth(int m) {
    month = m;
}

bool DBDate8::IsLeapYear(int year) {
    if ((year % 400) == 0) return true;
    else if ((year % 100) == 0) return false;
    else if ((year % 4) == 0) return true;
    else return false;
}

int DBDate8::GetDaysInMonth(int month, int year) {

    if (IsLeapYear(year)) {
        return arrDaysInLeapMonths[month];
    }
    else return arrDaysInNonLeapMonths[month];
}

bool DBDate8::operator == (DBDate8& date)
{
    return this->GetDay() == date.GetDay() && this->GetMonth() == date.GetMonth() && this->GetYear() == date.GetYear();
}

bool DBDate8::operator != (DBDate8& date)
{
    return (this->GetDay() != date.GetDay()) || (this->GetMonth() != date.GetMonth()) || (this->GetYear() != date.GetYear());
}

bool DBDate8::operator < (DBDate8& date) {
    return (this->GetDay() + this->GetMonth() * 100 + this->GetYear() * 10000) < (date.GetDay() + date.GetMonth() * 100 + date.GetYear() * 10000);
}

bool DBDate8::operator > (DBDate8& date) {
    return (this->GetDay() + this->GetMonth() * 100 + this->GetYear() * 10000) > (date.GetDay() + date.GetMonth() * 100 + date.GetYear() * 10000);
}

bool DBDate8::operator <= (DBDate8& date) {
    return (this->GetDay() + this->GetMonth() * 100 + this->GetYear() * 10000) <= (date.GetDay() + date.GetMonth() * 100 + date.GetYear() * 10000);
}

bool DBDate8::operator >= (DBDate8& date) {
    return (this->GetDay() + this->GetMonth() * 100 + this->GetYear() * 10000) >= (date.GetDay() + date.GetMonth() * 100 + date.GetYear() * 10000);
}


/*ostream& dbmsLib::DBDate8::operator<<(DBDate8& date)
{
    // TODO: вставьте здесь оператор return
    return out << date.GetDay() << "." << date.GetMonth() << "." << date.GetYear();
}*/
DBDate8& DBDate8::operator+=(int days) {
    while (day + days > GetDaysInMonth(month, year)) {
        days -= GetDaysInMonth(month, year);
        if (++month > 12) {
            month = 1;
            year++;
        }
    }
    day += days;
    return *this;
    /*if(day+days>GetDaysInMonth(month,year)){
        days=days-GetDaysInMonth(month,year);
        if(++month>12){
            month=1;
            year++;
        }
        while(days/GetDaysInMonth(month,year)){
            if(++month>12){
                month=1;
                year++;
            }
            days-=GetDaysInMonth(month,year);
        }
        day=days;
    }
    else day+=days;
    return *this;*/
}


DBDate8& DBDate8::operator-=(int days) {
    if (day - days < 1) {
        days -= day;
        if (--month == 0) {
            month = 12;
            year--;
        }
        while (days / GetDaysInMonth(month, year)) {
            days -= GetDaysInMonth(month, year);
            if (--month == 0) {
                month = 12;
                year--;
            }
        }
        day = GetDaysInMonth(month, year) - days;
    }
    else day -= days;
    return *this;
}

int DBDate8::DaysInCurYear() {
    int num = GetDay();
    for (int i = 1; i < GetMonth(); i++) num += GetDaysInMonth(i, GetYear());
    return num;
}

int DBDate8::operator-(DBDate8& date) {
    int dateDay = date.GetDay(), dateMonth = date.GetMonth(), dateYear = date.GetYear();
    int daysdate = 0;
    int yourDays = 0;
    for (int i = 1; i < dateYear; i++) {
        if (IsLeapYear(i)) daysdate += 366;
        else daysdate += 365;
    }
    daysdate += date.DaysInCurYear();
    for (int i = 1; i < GetYear(); i++) {
        if (IsLeapYear(i)) yourDays += 366;
        else yourDays += 365;
    }
    yourDays += DaysInCurYear();
    return yourDays - daysdate;
}

