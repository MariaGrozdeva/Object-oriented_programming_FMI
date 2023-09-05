#pragma once
#include "../Event/Event.h"

class EventCollection {
private:
    Event *eventCollection;
    unsigned int numberOfEvents = 0;

    void copyFrom(const EventCollection& other);
    void free();

private:
    EventCollection(Event* eventCollection);

    EventCollection() = default;
    EventCollection(const EventCollection& other);
    EventCollection& operator=(const EventCollection& other);
    ~EventCollection();

    void setCollection(Event *collection);
    void setNumberOfEvents(unsigned int size);

    Event* getCollection() const;
    unsigned int getNumberOfEvents() const;

    void addEvent(const Event event);
    void removeEvent(char* eventName);
    Event longestEvent() const;
    unsigned int availableEventsForThisTime(const Date& date) const;
};

