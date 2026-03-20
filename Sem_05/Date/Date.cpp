#include "Date.h"

#include <iostream>
#include <iomanip>

namespace
{
	bool isLeapYear(unsigned year)
	{
		if (year <= 1916)
		{
			return year % 4 == 0;
		}
		return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
	}
}

Date::Date(unsigned day, unsigned month, unsigned year)
{
	this->year = year;
	maxDays[1] = isLeapYear(year) ? 29 : 28;
	this->month = month;
	this->day = day;

	if (!isDateValid())
	{
		this->day = 1;
		this->month = 1;
		this->year = 1;
		maxDays[1] = 28;
	}

	isModified = true;
}

bool Date::setYear(unsigned year)
{
        unsigned oldYear = this->year;
        unsigned oldFebruaryDays = maxDays[1];

        this->year = year;
        maxDays[1] = isLeapYear(year) ? 29 : 28;

        if (!isDateValid())
        {
                this->year = oldYear;
                maxDays[1] = oldFebruaryDays;
                return false;
        }

        isModified = true;
        return true;
}

bool Date::setMonth(unsigned month)
{
        unsigned oldMonth = this->month;
        this->month = month;
        if (!isDateValid())
        {
                this->month = oldMonth;
                return false;
        }
        isModified = true;
        return true;
}

bool Date::setDay(unsigned day)
{
        unsigned oldDay = this->day;
        this->day = day;
        if (!isDateValid())
        {
                this->day = oldDay;
                return false;
        }
        isModified = true;
        return true;
}

unsigned Date::getYear() const
{
	return year;
}

unsigned Date::getMonth() const
{
	return month;
}

unsigned Date::getDay() const
{
	return day;
}

unsigned Date::getDayOfWeek() const
{
	if (!isModified)
	{
		return dayOfWeek;
	}

	Date date(1, 1, 1);
	unsigned dayOfWeek = 5; // 0-Monday, 1-Tuesday,.., 6-Sunday (On 01.01.01 was Saturday)

	while (compareDates(*this, date) != 0) // simple and dumb algorithm
	{
		date.goNextDay();
		(dayOfWeek += 1) %= 7;
	}

	this->dayOfWeek = dayOfWeek;
	isModified = false;
	return this->dayOfWeek;
}

void Date::goNextDay()
{
	if (compareDates(*this, Date(31, 3, 1916)) == 0)
	{
		setDay(14);
		setMonth(4);
		return;
	}

	day++;
	if (day > maxDays[month - 1])
	{
		day = 1;
		setMonth(month == 12 ? 1 : month + 1);

		if (month == 1)
		{
			setYear(year + 1);
		}
	}
}

void Date::serialize(std::ostream& os) const
{
	using namespace std;
	os << setw(2) << setfill('0') << day << '.' << setw(2) << setfill('0') << month << '.';
	os << setw(4) << setfill('0') << year << endl;
}

bool Date::isDateValid() const
{
	return !((month == 0 || month > 12)
		|| (day == 0 || day > maxDays[month - 1])
		|| (year == 0)
		|| (year == 1916 && month == 4 && day < 14)); // due to the transition from Julian to Gregorian
}

int compareDates(const Date& lhs, const Date& rhs)
{
        if (lhs.getYear() != rhs.getYear())
        {
                return lhs.getYear() < rhs.getYear() ? -1 : 1;
        }
        if (lhs.getMonth() != rhs.getMonth())
        {
                return lhs.getMonth() < rhs.getMonth() ? -1 : 1;
        }
        if (lhs.getDay() != rhs.getDay())
        {
                return lhs.getDay() < rhs.getDay() ? -1 : 1;
        }
        return 0;
}
