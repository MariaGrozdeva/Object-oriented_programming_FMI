#include "Date.h"

Date::Date(size_t day, size_t month, size_t year)
{
	update(day, month, year);
}

size_t Date::getYear() const
{
	return year;
}
size_t Date::getMonth() const
{
	return month;
}
size_t Date::getDay() const
{
	return day;
}

void Date::setYear(size_t year)
{
	this->year = year;

	if (isLeapYear())
		maxDays[1] = 29; // February
	else
		maxDays[1] = 28; // If the previously set year was a leap year.

	isChanged = true;
}
void Date::setMonth(size_t month)
{
	if (month > 12)
		month = 1;

	this->month = month;

	isChanged = true;
}
void Date::setDay(size_t day)
{
	if (day > maxDays[month - 1])
		day = 1;
	if (year == 1916 && month == 4 && day < 14)
		day = 14;

	this->day = day;

	isChanged = true;
}

bool Date::areEqual(const Date& other) const
{
	return year == other.year && month == other.month && day == other.day;
}

void Date::goNextDay()
{
	if (areEqual(Date(31, 3, 1916)))
	{
		setDay(14);
		setMonth(4);
		return;
	}

	setDay(day + 1);
	if (day == 1)
	{
		setMonth(month + 1);
		if (month == 1)
			setYear(year + 1);
	}
}
size_t Date::getDayOfWeek() const
{
	Date date(1, 1, 1);
	size_t dayOfWeek = 5; // 0-Monday, 1-Tuesday,.., 6-Sunday (On 01.01.01 was Saturday)

	while (!areEqual(date))
	{
		date.goNextDay();
		(dayOfWeek += 1) %= 7;
	}

	this->dayOfWeek = dayOfWeek + 1;
	isChanged = false;
	
	return this->dayOfWeek;
}

void Date::update(size_t day, size_t month, size_t year)
{
	setYear(year);
	setMonth(month);
	setDay(day);

	isChanged = true;
}

void Date::print() const
{
	std::cout << std::setw(2) << std::setfill('0') << day << '.' << std::setw(2) << std::setfill('0') << month << '.';
	std::cout << std::setw(4) << std::setfill('0') << year;
}

bool Date::isLeapYear() const
{
	if (year <= 1916)
		return year % 4 == 0;

	return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}