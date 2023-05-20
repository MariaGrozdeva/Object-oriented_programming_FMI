#include "Date.h"

bool isLeapYear(unsigned int year)
{
	if (year <= 1916)
	{
		return year % 4 == 0;
	}
	return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

Date::Date() :year(1), month(1), day(1), dayOfWeek(5)
{}

Date::Date(unsigned int year, unsigned int month, unsigned int day)
{
	setYear(year);
	setMonth(month);
	setDay(day);	
}

unsigned int Date::getDayOfWeek() const
{
	if (!isModified)
	{
		return dayOfWeek;
	}

	Date date(1, 1, 1);
	unsigned int dayOfWeek = 4; 
	// 0-Monday, 1-Tuesday,.., 6-Sunday (On 01.01.01 was Friday)

	while (!isEqualTo(date))
	{
		date.getNextDay();
		(dayOfWeek += 1) %= 7;
	}

	this->dayOfWeek = dayOfWeek + 1;
	isModified = false;

	return this->dayOfWeek;
}

bool Date::isEqualTo(const Date& other) const
{
	return year == other.year && month == other.month && day == other.day;
}

Date Date::getNextDay()
{
	Date newDate(year, month, day);

	setDay(newDate.day + 1);
	if (newDate.day == 1)
	{
		setMonth(newDate.month + 1);
		if (newDate.month == 1)
		{
			setYear(newDate.year + 1);
		}
	}

	return newDate;
}

void Date::setYear(unsigned int year)
{
	if (isLeapYear(year))
	{
		maxDays[1] = 29; // February
	}
	else
	{
		maxDays[1] = 28;
	}

	this->year = year;
	isModified = true;
}
void Date::setMonth(unsigned int month)
{
	if (month == 0 || month > 12)
	{
		month = 1;
	}

	this->month = month;
	isModified = true;
}
void Date::setDay(unsigned int day)
{
	if (day == 0 || day > maxDays[month - 1])
	{
		day = 1;
	}

	this->day = day;
	isModified = true;
}

unsigned int Date::getYear() const
{
	return year;
}
unsigned int Date::getMonth() const
{
	return month;
}
unsigned int Date::getDay() const
{
	return day;
}

void Date::print() const
{
	std::cout << std::setw(2) << std::setfill('0') << day << '.' << std::setw(2) << std::setfill('0') << month << '.';
	std::cout << std::setw(4) << std::setfill('0') << year;
}
