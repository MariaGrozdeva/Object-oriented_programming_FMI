#pragma once

#include "Time.h"
#include "Date.h"

const unsigned MAX_NAME_SIZE = 32;

class Event
{
private:
	char name[MAX_NAME_SIZE];
	Date date;
	Time startTime;
	Time endTime;

	void setName(const char* name);

public:
	Event();
	Event(const char* name, Date date, Time startTime, Time endTime);
	Event(const char* name, unsigned int year, unsigned int month, unsigned int day, unsigned int sHours, unsigned int sMinutes, unsigned int sSeconds, unsigned int eHours, unsigned int eMinutes, unsigned int eSeconds);

	const char* getName() const;
	const Date getDate() const;
	const Time getStartTime() const;
	const Time getEndTime() const;

	int getEventsDayOfWeek() const;

	void validateTimes();

	void print() const;
};
