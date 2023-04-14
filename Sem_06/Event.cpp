#include "Event.h"

Event::Event(const char* name, const Date& date, const Time& startingTime, unsigned int duration)
	: date(date),
	startTime(startingTime),
	duration(duration)
{
	strcpy_s(this->name, 128, name);
}

unsigned int Event::getDayOfWeek() const
{
	return date.getDayOfWeek();
}

void Event::print() const
{
	std::cout << "Event name: " << name << std::endl;
	std::cout << "Date of event: ";
	date.print();
	std::cout << std::endl;
	std::cout << "Starting time: ";
	startTime.print(false);
	unsigned int minutes = duration / 60;
	std::cout << "Duration: " << minutes / 60 << "h " << minutes % 60 << "m" << std::endl;
}

