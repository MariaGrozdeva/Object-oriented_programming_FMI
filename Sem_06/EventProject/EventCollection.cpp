#include "EventCollection.h"

EventCollection::EventCollection() : cntEvents(0), events(nullptr), capacity(8)
{}

EventCollection::EventCollection(const EventCollection & other)
{
	copyFrom(other);
}

EventCollection& EventCollection::operator=(const EventCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

EventCollection::~EventCollection()
{
	free();
}

void EventCollection::addEvent(Event event)
{
	if (cntEvents == capacity)
	{
		resize(capacity * 2);
	}

	events[cntEvents] = event;
	cntEvents++;
}

void EventCollection::removeEventByName(const char* name)
{
	// Validate cntEvents
	if (cntEvents == 0)
	{
		std::cout << "There are no events in the collection to remove!" << std::endl;
		return;
	}

	for (size_t i = 0; i < cntEvents; i++)
	{
		if (strcmp(events[i].getName(), name) == 0)
		{
			for (size_t j = i; j < cntEvents - 1; j++)
			{
				events[j] = events[j + 1];
			}

			--cntEvents;
			if (cntEvents == capacity / 2)
			{
				resize(capacity / 2);
			}

			break;
		}
	}
}

Event EventCollection::theLongestEvent() const
{
	// Validate cntEvents
	if (cntEvents == 0)
	{
		std::cout << "There are no events in the collection!" << std::endl;
		return Event("No events today", Date(), Time(), Time());
	}

	unsigned int longestEventInSeconds = 0;
	unsigned int currEventInSeconds = 0;
	size_t ind = 0;

	for (size_t i = 0; i < cntEvents; i++)
	{
		currEventInSeconds = events[i].getEndTime().convertToSeconds() - events[i].getStartTime().convertToSeconds();

		if (longestEventInSeconds < currEventInSeconds)
		{
			longestEventInSeconds = currEventInSeconds;
			ind = i;
		}
	}

	Event ev(events[ind].getName(), events[ind].getDate(), events[ind].getStartTime(), events[ind].getEndTime());
	return ev;
}

int EventCollection::maxEventsToVisit(Date date) const
{
	// Validate cntEvents
	if (cntEvents == 0)
	{
		std::cout << "There are no events in the collection!" << std::endl;
		return -1;
		// We return -1 because we may have a collection of events and if on the given date there is no event registered then we will return 0 
	}

	// Finding all the events that occur on the given date
	Event* eventsOnDate = new Event[cntEvents];
	size_t cntEventsOnDate = 0;

	for (size_t i = 0; i < cntEvents; i++)
	{
		if (events[i].getDate().isEqualTo(date))
		{
			eventsOnDate[cntEventsOnDate] = events[i];
			cntEventsOnDate++;
		}
	}

	// Find the maximum number of non-overlapping events
	int maxEvents = 0;

	for (size_t i = 0; i < cntEventsOnDate; i++)
	{
		int numEvents = 1;

		// Example: Event1 => 15:00:00 & 15:30:00 || Event2 => 16:00::00 & 17:00:00 || Event3 => 16:30:00 & 17:00:00
		for (size_t j = i + 1; j < cntEventsOnDate; j++)
		{
			if (eventsOnDate[i].getEndTime().compare(eventsOnDate[j].getStartTime()) <= 0)
			{
				numEvents++;
				i = j;
			}
		}

		if (numEvents > maxEvents)
		{
			maxEvents = numEvents;
		}
	}

	return maxEvents;
}

void EventCollection::free()
{
	delete[] events;
	events = nullptr;
}

void EventCollection::copyFrom(const EventCollection& eventColection)
{
	cntEvents = eventColection.cntEvents;
	capacity = eventColection.capacity;

	events = new Event[capacity];
	for (size_t i = 0; i < cntEvents; i++)
	{
		events[i] = eventColection.events[i];
	}
}

void EventCollection::resize(unsigned int newCapacity)
{
	Event* temp = events;
	events = new Event[newCapacity];

	for (size_t i = 0; i < cntEvents; i++)
	{
		events[i] = temp[i];
	}

	capacity = newCapacity;
	delete[] temp;
}