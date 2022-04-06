#pragma once
#include <iostream>

class Time
{
private:
	size_t hours;
	size_t minutes;
	size_t seconds;

	size_t convertToSeconds() const;
	Time getDiff(const Time& other) const;

public:
	Time();
	Time(size_t seconds);
	Time(size_t hours, size_t minutes, size_t seconds);

	int compare(const Time& other) const;

	Time getToMidnight() const;;

	bool isDinnerTime() const;
	bool isPartyTime() const;

	void print(bool is12hoursClock) const;

	void setHours(size_t hours);
	void setMinutes(size_t minutes);
	void setSeconds(size_t seconds);

	size_t getHours() const;
	size_t getMinutes() const;
	size_t getSeconds() const;
};