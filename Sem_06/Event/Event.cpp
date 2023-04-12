#include "Event.h"
#include <cstring>

#pragma warning (disable : 4996)

void Event::copyFrom(const Event& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	eventDate = other.eventDate;
	startTime = other.startTime;
    endTime = other.endTime;
}

void Event::free()
{
	delete[] name;
	name = nullptr;
}

Event::Event(const char *name, const Date eventDate, const Time startTime, const Time endTime)
{
    setName(name);
    setDate(eventDate);
    setStartTime(startTime);
    setEndTime(endTime);
}

Event::Event(const Event& other)
{
	copyFrom(other);
}

Event& Event::operator=(const Event& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Event::~Event()
{
	free();
}

void Event::setName(const char* name)
{
	if (this->name == name)
	{
		return;
	}

	delete[] this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Event::setDate(Date eventDate)
{
	this->eventDate = eventDate;
}

void Event::setStartTime(Time startTime)
{
    this->startTime = startTime;
}

void Event::setEndTime(Time endTime)
{
    this->endTime = endTime;
}

char* Event::getName() const
{
	return this->name;
}

Date Event::getDate() const
{
	return this->eventDate;
}

Time Event::getStartTime() const
{
    return startTime;
}

Time Event::getEndTIme() const
{
    return endTime;
}

unsigned int Event::getDayOfWeek() const
{
	return this->eventDate.getDayOfWeek();
}

void Event::print() const
{
	std::cout << "Event name: " << this->getName() << std::endl;
	std::cout << "Event date: " << this->eventDate.getDay() << "-" << this->eventDate.getMonth() << "-" << this->eventDate.getYear() << std::endl;
    std::cout << "Start time: " << this->startTime.getHours() << ":" << this->startTime.getMinutes() << ":" << this->startTime.getSeconds() << std::endl;
    std::cout << "End time: " << this->endTime.getHours() << ":" << this->endTime.getMinutes() << ":" << this->endTime.getSeconds() << std::endl;
}

unsigned int Event::getDuration() const
{
	unsigned int duration = 0;

	unsigned int h = endTime.getHours() - startTime.getHours();
	unsigned int m = endTime.getMinutes() - startTime.getMinutes();
	unsigned int s = endTime.getSeconds() - startTime.getSeconds();

	// базови проверки за коректност на времето

	if (h < 0)
	{
		h += 24;
	}

	if (m < 0)
	{
		m += 60;
		h--;
	}

	if (s < 0)
	{
		s += 60;
		m--;
	}

	duration = h * 3600 + m * 60 + s;
	return duration;
}