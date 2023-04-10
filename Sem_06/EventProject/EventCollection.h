#pragma once

#include "Event.h"

class EventCollection
{
private:
	Event* events;
	size_t cntEvents;
	size_t capacity;

private:
	void free();
	void copyFrom(const EventCollection& eventColection);

	void resize(unsigned int newCapacity);

public:

	EventCollection();
	EventCollection(const EventCollection& other);
	EventCollection& operator=(const EventCollection& other);
	~EventCollection();

	void addEvent(Event event);

	void removeEventByName(const char* name);

	Event theLongestEvent() const;

	int maxEventsToVisit(Date date) const;
};
