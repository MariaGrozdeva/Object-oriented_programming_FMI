#pragma once
#pragma warning (disable : 4996)

#include "Time.h"
#include "Date.h"

const unsigned MAX_NAME_SIZE = 32;

class Event
{
private:
	char name[MAX_NAME_SIZE];
	Date date;
	Time startTime;

	void setName(const char* name);

public:
	Event(const char* name, const Date& date, const Time& startTime);
	Event(const char* name, size_t day, size_t month, size_t year, size_t hours, size_t minutes, size_t seconds);

	const char* getName() const;
	const Date& getDate() const;
	const Time& getTime() const;

	int getEventsDayOfWeek() const;

	void print() const;
};