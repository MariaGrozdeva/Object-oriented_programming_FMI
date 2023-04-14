#pragma once

#include "Date.h"
#include "Time.h"

class Event
{
private:
	char name[128];
	Date date;
	Time startTime;
	unsigned int duration;
public:
	Event()
		: Event("Unknown", Date(1, 1, 1), Time(1), 1) {}
	Event(const char* name, const Date& date, const Time& startingTime, unsigned int duration);

	const char* getName() const { return name; }
	Date getDate() const { return date; }
	Time getStartingTime() const { return startTime; }
	unsigned int getDuration() const { return duration; }

	unsigned int getDayOfWeek() const;
	void print() const;
};

