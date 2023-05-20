#include <iostream>
#include "EventCollection.h"


int main()
{
	EventCollection ec;
	Event ev1("Birthday", 2001, 3, 1, 12, 34, 00, 13, 45, 00);
	Event ev2("Name Day", 2023, 4, 4, 16, 22, 00, 11, 45, 00);
	Event ev3("New Year", 2022, 1, 1, 1, 0, 0, 2, 0, 0);
	Event ev4("New Year", 2022, 1, 1, 2, 0, 0, 3, 0, 0);
	Event ev5("New Year", 2022, 1, 1, 3, 0, 0, 4, 0, 0);
	Event ev6("New Year", 2022, 1, 1, 3, 30, 0, 4, 0, 0);
	Event ev7("Christmas Day", 2022, 12, 24, 20, 0, 0, 23, 0, 0);

	ec.addEvent(ev1);
	ec.addEvent(ev2);
	ec.addEvent(ev3);
	ec.addEvent(ev4);
	ec.addEvent(ev5);
	ec.addEvent(ev6);
	ec.addEvent(ev7);

	ec.removeEventByName("Name Day");

	Date date(2022, 1, 1);
	int max = ec.maxEventsToVisit(date);
	Event longestEvent = ec.theLongestEvent();

	std::cout << "Max number events which can be visited during ";
	date.print();
	std::cout << " are: " << max << std::endl;
	longestEvent.print();

}
