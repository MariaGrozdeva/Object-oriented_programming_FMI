#include "Time.h"

Time::Time() : Time(0, 0, 0)
{}

Time::Time(size_t seconds)
{
	hours = seconds / 3600;
	seconds %= 3600;

	minutes = seconds / 60;
	seconds %= 60;

	this->seconds = seconds;
}
Time::Time(size_t hours, size_t minutes, size_t seconds)
{
	setHours(hours);
	setMinutes(minutes);
	setSeconds(seconds);
}

int Time::compare(const Time& other) const
{
	size_t thisSeconds = convertToSeconds();
	size_t otherSeconds = other.convertToSeconds();

	if (thisSeconds > otherSeconds)
		return 1;
	else if (thisSeconds < otherSeconds)
		return -1;
	else
		return 0;
}

Time Time::getToMidnight() const
{
	Time midnight(23, 59, 59); // Can't be 00:00:00, because getDiff would return a wrong difference.
	return getDiff(midnight); // So here the time should be incremented by one second.
}

bool Time::isDinnerTime() const
{
	Time startingHour(20, 30, 0);
	Time endingHour(22, 0, 0);

	return compare(startingHour) >= 0 && compare(endingHour) <= 0;
}
bool Time::isPartyTime() const
{
	Time startingHour(23, 0, 0);
	Time endingHour(6, 0, 0);

	return compare(startingHour) >= 0 || compare(endingHour) <= 0;
}

void Time::print(bool is12hoursClock) const
{
	if (hours < 10)
		std::cout << 0;
	std::cout << ((is12hoursClock && hours > 12) ? hours - 12 : hours) << ':';

	if (minutes < 10)
		std::cout << 0;
	std::cout << minutes << ':';

	if (seconds < 10)
		std::cout << 0;
	std::cout << seconds;

	if (is12hoursClock)
		std::cout << ((hours > 12) ? "PM" : "AM");
	std::cout << std::endl;
}

void Time::setHours(size_t hours)
{
	if (hours > 23)
		hours = 23;
	this->hours = hours;
}
void Time::setMinutes(size_t minutes)
{
	if (minutes > 59)
		minutes = 59;
	this->minutes = minutes;
}
void Time::setSeconds(size_t seconds)
{
	if (seconds > 59)
		seconds = 59;
	this->seconds = seconds;
}

size_t Time::getHours() const
{
	return hours;
}
size_t Time::getMinutes() const
{
	return minutes;
}
size_t Time::getSeconds() const
{
	return seconds;
}

size_t Time::convertToSeconds() const
{
	return 3600 * hours + 60 * minutes + seconds;
}
Time Time::getDiff(const Time& other) const
{
	size_t thisSeconds = convertToSeconds();
	size_t otherSeconds = other.convertToSeconds();

	size_t diff;

	if (thisSeconds > otherSeconds)
		diff = thisSeconds - otherSeconds;
	else
		diff = otherSeconds - thisSeconds;

	return Time(diff);
}
