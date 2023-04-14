#include "EventCollection.h"

EventCollection::EventCollection(const EventCollection& other)
	: events(nullptr),
	eventsCount(0),
	capacity(8)
{
	copyFrom(other);
}

EventCollection& EventCollection::operator=(const EventCollection& other)
{
	if (this != &other)
		copyFrom(other);

	return *this;
}

void EventCollection::copyFrom(const EventCollection& other)
{
	copyEvents(other.events, other.eventsCount, other.capacity);
	eventsCount = other.eventsCount;
	capacity = other.capacity;
}

void EventCollection::free()
{
	delete[] events;
	events = nullptr;
}

void EventCollection::copyEvents(const Event* collection, unsigned int count, unsigned int capacity)
{
	Event* newEvents = new (std::nothrow) Event[capacity];
	if (!newEvents)
	{
		std::cout << "Memory allocation failed!" << std::endl;
		return;
	}

	for (int i = 0; i < count; ++i)
	{
		newEvents[i] = collection[i];
	}

	delete[] events;
	events = newEvents;
}

void EventCollection::addEvent(const Event& event)
{
	if (eventsCount == 0)
	{
		events = new Event[capacity];
	}
	if (eventsCount == capacity)
	{
		expandDynamicArray();
	}
	eventsCount++;
	events[eventsCount - 1] = event;
}

void EventCollection::removeEvent(const char* name)
{
	int eventInd = getEventByName(name);
	if (eventInd == -1)
	{
		return;
	}

	eventsCount--;
	if (eventsCount == 0)
	{
		free();
		return;
	}

	for (int i = 0; i < eventInd; ++i)
	{
		events[i] = events[i];
	}
	for (int i = eventInd; i < eventsCount; ++i)
	{
		events[i] = events[i + 1];
	}
	

	if (eventsCount * 2 == capacity)
	{
		shrinkDynamicArray();
	}
}

int EventCollection::getEventByName(const char* name) const
{
	for (int i = 0; i < eventsCount; ++i)
	{
		if (strcmp(name, events[i].getName()) == 0)
			return i;
	}

	return -1;
}

void EventCollection::expandDynamicArray()
{
	copyEvents(events, eventsCount, capacity * 2);
	capacity *= 2;
}

void EventCollection::shrinkDynamicArray()
{
	copyEvents(events, eventsCount, capacity / 2);
	capacity /= 2;
}

void EventCollection::printEvents() const
{
	std::cout << "Total events: " << eventsCount << std::endl;
	for (int i = 0; i < eventsCount; ++i)
	{
		events[i].print();
	}
	std::cout << std::endl;
}

void EventCollection::getLongestEvent() const
{
	if (eventsCount == 0)
	{
		return;
	}
	unsigned int longestEventInd = 0;
	for (int i = 0; i < eventsCount; ++i)
	{
		if (events[i].getDuration() > events[longestEventInd].getDuration())
			longestEventInd = i;
	}

	unsigned int minutes = events[longestEventInd].getDuration() / 60;
	std::cout << "Longest event is \"" << events[longestEventInd].getName() << "\" with duration " << minutes / 60 << "h " << minutes % 60 << "m" << std::endl << std::endl;
}

unsigned int EventCollection::getMaxEventsToAttend(const Date& date) const
{
	unsigned int totalEvents = 0;
	for (int i = 0; i < eventsCount; ++i)
	{
		Date currDate = events[i].getDate();
		if (!currDate.isEqualTo(date))
			continue;

		totalEvents++;
		if (totalEvents == 1)
			continue;

		if (!isValidEvent(date, i))
			totalEvents--;
	}

	return totalEvents;
}

bool EventCollection::isValidEvent(const Date& date, unsigned int eventInd) const 
{
	Time start = events[eventInd].getStartingTime();
	Time end(events[eventInd].getDuration() + start.convertToSeconds());

	for (int j = 0; j < eventInd; ++j)
	{
		Date currDate = events[j].getDate();
		if (!currDate.isEqualTo(date))
			continue;

		Time startCurr = events[j].getStartingTime();
		Time endCurr(events[j].getDuration() + startCurr.convertToSeconds());
		if (start.compare(endCurr) == -1 && end.compare(startCurr) == 1)
			return false;
	}
	return true;
}
