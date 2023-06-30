#include <dbmsLib5.h> 
#include <string>
#include <strstream>
using namespace dbmsLib5;

const int DBDate5::arrDays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

DBDate5::DBDate5 (string date) {
	int d = stoi(date.substr(0, date.find_first_of(".")));
	int m = stoi(date.substr(date.find_first_of(".") + 1, date.find_last_of(".")));
	int y = stoi(date.substr(date.find_last_of(".") + 1));
	
	if (y > 0 && y < 10000 && m > 0 && m < 13 && d > 0 && d <= GetDaysInMonth(m,y)) {
		day = d;
		month = m;
		year = y;
	} else {
		cout << "Недопустимая дата! Установлена 1.1.1\n";
		day = 1;
		month = 1;
		year = 1;
	}
}

DBDate5::DBDate5 (int d, int m, int y) {
	if (y > 0 && y < 10000 && m > 0 && m < 13 && d > 0 && d <= GetDaysInMonth(m,y)) {
		day = d;
		month = m;
		year = y;
	} else {
		cout << "Недопустимая дата! Установлена 1.1.1\n";
		day = 1;
		month = 1;
		year = 1;
	}	
}


bool DBDate5::IsLeapYear(int year) {
	if (year % 400 == 0) {
		return true;
	}
	else {
		return (year % 4 == 0 && year & 100 != 0);
	}
}

int DBDate5::GetDay() { return day; }
int DBDate5::GetMonth() { return month; }
int DBDate5::GetYear() { return year; }

int DBDate5::GetDaysInMonth(int month, int year) {
	int days_in_month = arrDays[month];
	if (IsLeapYear(year) && month == 2) days_in_month + 1;
	return days_in_month;
}

int DBDate5::DaysInCurYear() {
	int days = 0;
	for (int i = 1; i < month; ++i)
	{
		if (i == 2 && IsLeapYear(year)) days += 1;
		days += arrDays[i];
	}
	days += day;
	return days;
}


bool DBDate5::operator==(DBDate5& date)
{
	return (day == date.day && month == date.month && year == date.year);
}
bool DBDate5::operator<(DBDate5& date)
{
	if(year != date.year)
	{
		return year < date.year;
	}
	else

	{
		if(month != date.month)
		{
			return month < date.month;
		}
		else
		{
			if(day != date.day)
			{
				return day < date.month;
			}
			else
			{
				return false;
			}
		}
	}
}
bool DBDate5::operator>(DBDate5& date) {
	if(year != date.year)
	{
		return year > date.year;
	}
	else

	{
		if(month != date.month)
		{
			return month > date.month;
		}
		else
		{
			if(day != date.day)
			{
				return day > date.month;
			}
			else
			{
				return false;
			}
		}
	}
}
bool DBDate5::operator<= (DBDate5& date)
{
	return !(*this > date);
}
bool DBDate5::operator>= (DBDate5& date)
{
	return !(*this < date);
}
bool DBDate5::operator!= (DBDate5& date)
{
	return !(*this == date);
}

string dbmsLib5::DateToStr(DBDate5& date) {
	char buffer[12];
	strstream stream(buffer, 12);
	stream << date.day << "." << date.month << "." << date.year << '\0';
	return buffer;
}

ostream& dbmsLib5::operator<<(ostream& out,DBDate5& date) {
	return out << DateToStr(date);
}

/*int DBDate5::operator-(DBDate5& date) {
	int cur_month_days = DBDate5::arrDays[this->month];
	if (IsLeapYear(this->year)) {
		++cur_month_days;
	} 
	int current_days = this->day +
}*/