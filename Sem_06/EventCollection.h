#pragma once
#include "Event.h"

class EventCollection
{
private:
	Event* events;
	unsigned int eventsCount;
	unsigned int capacity;
private:
	void copyFrom(const EventCollection& other);
	void free();
	void copyEvents(const Event* collection, unsigned int count, unsigned int capacity);
	void expandDynamicArray();
	void shrinkDynamicArray();
	bool isValidEvent(const Date& date, unsigned int eventInd) const;
public:
	EventCollection()
		: events(nullptr),
		eventsCount(0),
		capacity(8) {}

	EventCollection(const EventCollection& other);
	EventCollection& operator=(const EventCollection& other);

	~EventCollection()
	{
		free();
	}

	void addEvent(const Event& event);
	void removeEvent(const char* name);
	int getEventByName(const char* name) const;

	void printEvents() const;
	void getLongestEvent() const;
	unsigned int getMaxEventsToAttend(const Date& date) const;
};
