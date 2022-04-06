#include "Event.h"

Event::Event(const char* name, const Date& date, const Time& startTime) : date(date), startTime(startTime)
{
	setName(name);
}
Event::Event(const char* name, size_t day, size_t month, size_t year, size_t hours, size_t minutes, size_t seconds) : date(day, month, year), startTime(hours, minutes, seconds)
{
	setName(name);
}

const char* Event::getName() const
{
	return name;
}
const Date& Event::getDate() const
{
	return date;
}
const Time& Event::getTime() const
{
	return startTime;
}

int Event::getEventsDayOfWeek() const
{
	return date.getDayOfWeek();
}

void Event::print() const
{
	std::cout << "Event: " << name << ", Date: ";
	date.print();
	std::cout << ", Time: ";
	startTime.print(true);
	std::cout << std::endl;
}

void Event::setName(const char* name)
{
	if (strlen(name) > MAX_NAME_SIZE)
		strcpy(this->name, "Unknown");
	else
		strcpy(this->name, name);
}