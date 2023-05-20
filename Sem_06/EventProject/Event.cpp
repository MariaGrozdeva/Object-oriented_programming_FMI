#include "Event.h"

void Event::validateTimes()
{
	int compare = startTime.compare(endTime);
	if (compare == 0)
	{
		endTime.addOneSecond();
	}
	else if (compare == 1)
	{
		// First option 
		/*Time temp(endTime);
		endTime = startTime;
		startTime = temp;*/

		// Second option
		Time temp(startTime.getHours(), startTime.getMinutes(), startTime.getSeconds());

		startTime.setHours(endTime.getHours());
		startTime.setMinutes(endTime.getMinutes());
		startTime.setSeconds(endTime.getSeconds());

		endTime.setHours(temp.getHours());
		endTime.setMinutes(temp.getMinutes());
		endTime.setSeconds(temp.getSeconds());
	}
}

Event::Event()
{
	setName("Unknown");
	validateTimes();
}

Event::Event(const char* name, Date date, Time startTime, Time endTime)
	:date(date), startTime(startTime), endTime(endTime)
{
	setName(name);
	validateTimes();
}

Event::Event(const char* name, unsigned int year, unsigned int month, unsigned int day, 
	unsigned int sHours, unsigned int sMinutes, unsigned int sSeconds, unsigned int eHours, unsigned int eMinutes, unsigned int eSeconds)
	: date(year, month, day), startTime(sHours, sMinutes, sSeconds), endTime(eHours, eMinutes, eSeconds)
{
	setName(name);
	validateTimes();
}

const char* Event::getName() const
{
	return name;
}

const Date Event::getDate() const
{
	return date;
}

const Time Event::getStartTime() const
{
	return startTime;
}

const Time Event::getEndTime() const
{
	return endTime;
}

int Event::getEventsDayOfWeek() const
{
	return date.getDayOfWeek();
}

void Event::print() const
{
	std::cout << "Event: " << name << ", Date: ";
	date.print();
	std::cout << ", Starts at: ";
	startTime.print(false);
	std::cout << ", Ends at: ";
	endTime.print(false);
	std::cout << std::endl;
}

void Event::setName(const char* name)
{
	if (strlen(name) > MAX_NAME_SIZE)
	{
		strcpy(this->name, "Unknown");
		this->name[strlen(name)] = '\0';
	}
	else
	{
		strcpy(this->name, name);
		this->name[strlen(name)] = '\0';
	}

}