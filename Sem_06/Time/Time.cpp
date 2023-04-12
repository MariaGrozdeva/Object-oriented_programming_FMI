#include "Time.h"

Time::Time() : Time(0, 0, 0)
{}
Time::Time(unsigned int seconds)
{
	hours = seconds / 3600;
	seconds %= 3600;

	minutes = seconds / 60;
	seconds %= 60;

	this->seconds = seconds;
}
Time::Time(unsigned int hours, unsigned int minutes, unsigned int seconds)
{
	setHours(hours);
	setMinutes(minutes);
	setSeconds(seconds);
}

int Time::compare(const Time& other) const
{
	unsigned int thisSeconds = convertToSeconds();
	unsigned int otherSeconds = other.convertToSeconds();

	if (thisSeconds > otherSeconds)
	{
		return 1;
	}
	else if (thisSeconds < otherSeconds)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

Time Time::getToMidnight() const
{
	Time midnight(23, 59, 59); // Can't be 00:00:00 because getDiff would return a wrong difference
	return getDiff(midnight);
}

bool Time::isDinnerTime() const
{
	Time startHour(20, 30, 0);
	Time endHour(22, 0, 0);

	return compare(startHour) >= 0 && compare(endHour) <= 0;
}
bool Time::isPartyTime() const
{
	Time startHour(23, 0, 0);
	Time endHour(6, 0, 0);

	return compare(startHour) >= 0 || compare(endHour) <= 0;
}

void Time::print(bool is12hoursClock) const
{
	std::cout << std::setfill('0');
	std::cout << std::setw(2) << ((is12hoursClock && hours > 12) ? hours - 12 : hours) << ':';
	std::cout << std::setw(2) << minutes << ':';
	std::cout << std::setw(2) << seconds;

	if (is12hoursClock)
	{
		std::cout << ((hours > 12) ? " PM" : " AM");
	}
	std::cout << std::endl;
}

void Time::setHours(unsigned int hours)
{
	if (hours > 23)
	{
		hours = 23;
	}
	this->hours = hours;
}
void Time::setMinutes(unsigned int minutes)
{
	if (minutes > 59)
	{
		minutes = 59;
	}
	this->minutes = minutes;
}
void Time::setSeconds(unsigned int seconds)
{
	if (seconds > 59)
	{
		seconds = 59;
	}
	this->seconds = seconds;
}

unsigned int Time::getHours() const
{
	return hours;
}
unsigned int Time::getMinutes() const
{
	return minutes;
}
unsigned int Time::getSeconds() const
{
	return seconds;
}

unsigned int Time::convertToSeconds() const
{
	return 3600 * hours + 60 * minutes + seconds;
}
Time Time::getDiff(const Time& other) const
{
	unsigned int thisSeconds = convertToSeconds();
	unsigned int otherSeconds = other.convertToSeconds();

	unsigned int diff = 0;
	if (thisSeconds > otherSeconds)
	{
		diff = thisSeconds - otherSeconds;
	}
	else
	{
		diff = otherSeconds - thisSeconds;
	}

	return Time(diff);
}