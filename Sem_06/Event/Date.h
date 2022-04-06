#pragma once
#include <iostream>
#include <iomanip>

class Date
{
private:
	size_t year;
	size_t month;
	size_t day;

	size_t maxDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	// These can be changed by constant functions.
	mutable size_t dayOfWeek;
	mutable bool isChanged;

	bool isLeapYear() const;

public:
	Date(size_t day, size_t month, size_t year);

	size_t getYear() const;
	size_t getMonth() const;
	size_t getDay() const;

	void setYear(size_t year);
	void setMonth(size_t month);
	void setDay(size_t day);

	bool areEqual(const Date& other) const;

	void goNextDay();
	size_t getDayOfWeek() const;

	void print() const;
};