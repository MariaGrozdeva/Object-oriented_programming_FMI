#pragma once

#include "../Date/Date.h"
#include "../Time/Time.h"
#include <iostream>


class Event
{
private:
	char* name = nullptr;
	Date eventDate;
    Time startTime;
    Time endTime;

	void copyFrom(const Event& other);
	void free();

public:
    Event(const char *name, Date eventDate, Time startTime, Time endTime);

    Event() = default;
	Event(const Event& other);
	Event& operator=(const Event& other);
	~Event();

	void setName(const char* name);
	void setDate(Date eventDate);
	void setStartTime(Time startTime);
    void setEndTime(Time endTime);

	char* getName() const;
	Date getDate() const;
	Time getStartTime() const;
    Time getEndTIme() const;

	unsigned int getDayOfWeek() const;
	void print() const;
	unsigned int getDuration() const;
};