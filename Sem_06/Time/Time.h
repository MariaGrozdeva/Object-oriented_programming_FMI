#pragma once

#include <iostream>
#include <iomanip>

class Time
{
private:
	unsigned int hours;
	unsigned int minutes;
	unsigned int seconds;

	unsigned int convertToSeconds() const;
	Time getDiff(const Time& other) const;

public:
	Time();
	Time(unsigned int seconds);
	Time(unsigned int hours, unsigned int minutes, unsigned int seconds);

	int compare(const Time& other) const;

	Time getToMidnight() const;

	bool isDinnerTime() const;
	bool isPartyTime() const;

	void print(bool is12hoursClock) const;

	void setHours(unsigned int hours);
	void setMinutes(unsigned int minutes);
	void setSeconds(unsigned int seconds);

	unsigned int getHours() const;
	unsigned int getMinutes() const;
	unsigned int getSeconds() const;
};