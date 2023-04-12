#include "EventCollection.h"
#include <cstring>
#pragma warning (disable : 4996)

EventCollection::EventCollection(Event* collection)
{
    setCollection(collection);
};

EventCollection::EventCollection(const EventCollection& other)
{
    copyFrom(other);
}

EventCollection& EventCollection::operator=(const EventCollection &other)
{
   if(this != &other)
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

void EventCollection::copyFrom(const EventCollection& other)
{
    eventCollection = new Event[other.numberOfEvents];
    numberOfEvents = other.numberOfEvents;
}

void EventCollection::free()
{
    delete [] eventCollection;
    eventCollection = nullptr;
}

Event* EventCollection::getCollection() const
{
    return eventCollection;
}

unsigned int EventCollection::getNumberOfEvents() const
{
    return numberOfEvents;
}

void EventCollection::setCollection(Event *collection)
{
    this->eventCollection = collection;
}

void EventCollection::setNumberOfEvents(unsigned int size)
{
    this->numberOfEvents = size;
}

void EventCollection::addEvent(const Event event)
{
    Event* newCollection = new Event[numberOfEvents + 1];

    for (int i = 0; i < numberOfEvents; i++)
    {
        newCollection[i] = eventCollection[i];
    }

    newCollection[numberOfEvents] = event;

    delete [] eventCollection;
    eventCollection = newCollection;

    numberOfEvents++;
}

void EventCollection::removeEvent(char* name)
{
    Event* newCollection = new Event[numberOfEvents - 1];

    for (int i = 0; i < numberOfEvents; i++)
    {
        if (strcmp(eventCollection[i].getName(), name) != 0)
        {
            newCollection[i] = eventCollection[i];
        }
    }

    delete [] eventCollection;
    eventCollection = newCollection;

    numberOfEvents--;
}

Event EventCollection::longestEvent() const
{
    Event longestEvent = eventCollection[0];

    for(int i = 0 ; i < numberOfEvents ; i++)
    {
        if(eventCollection[i].getDuration() > longestEvent.getDuration())
        {
            longestEvent = eventCollection[i];
        }
    }

    return longestEvent;
}

unsigned int EventCollection::availableEventsForThisTime(const Date& date) const
{
    int count = 0;

    for(int i = 0 ; i < numberOfEvents ; i ++)
    {
        if(!eventCollection[i].getDate().isEqualTo(date))
        {
            continue;
        }
        bool overlaps = false;

        for(int j = 0 ; j < numberOfEvents ; j++)
        {
            if(i == j)
            {
                continue;
            }

            if(eventCollection[i].getStartTime().compare(eventCollection[j].getStartTime())  < 0 &&
               eventCollection[i].getStartTime().compare(eventCollection[j].getEndTIme()) < 0)
            {
                overlaps = true;
                break;
            }
        }

        if(!overlaps)
        {
            count++;
        }
    }

    return count;
}