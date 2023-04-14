#pragma once

#include <iostream>
#include <iomanip>

class Date
{
private:
	unsigned int year;
	unsigned int month;
	unsigned int day;

	unsigned int maxDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	// These can be changed by constant functions.
	mutable unsigned int dayOfWeek;
	mutable bool isModified;

	void setYear(unsigned int year);
	void setMonth(unsigned int month);
	void setDay(unsigned int day);

public:
	Date(unsigned int day, unsigned int month, unsigned int year);

	unsigned int getDayOfWeek() const;

	bool isEqualTo(const Date& other) const;

	void goNextDay();

	void update(unsigned int day, unsigned int month, unsigned int year);

	void print() const;

	unsigned int getYear() const;
	unsigned int getMonth() const;
	unsigned int getDay() const;
};