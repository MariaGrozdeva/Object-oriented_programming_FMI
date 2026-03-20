#pragma once

#include <iostream>

class Date
{
private:
	unsigned day = 1;
	unsigned month = 1;
	unsigned year = 1;

	unsigned maxDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	// These can be changed by constant functions.
	mutable unsigned dayOfWeek = 0;
	mutable bool isModified = true;

	bool isDateValid() const;

public:
	Date(unsigned day, unsigned month, unsigned year);

	bool setYear(unsigned year);
	bool setMonth(unsigned month);
	bool setDay(unsigned day);

	unsigned getYear() const;
	unsigned getMonth() const;
	unsigned getDay() const;

	unsigned getDayOfWeek() const;

	void goNextDay();

	void serialize(std::ostream& os) const;
};

int compareDates(const Date& lhs, const Date& rhs);
