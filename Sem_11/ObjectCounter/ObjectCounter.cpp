#include "ObjectCounter.h"

unsigned ObjectCounter::count = 0;
unsigned ObjectCounter::nextID = 0;

ObjectCounter::ObjectCounter()
{
	++count;
	currentObjectID = nextID;
	nextID += IDstep;
}
ObjectCounter::~ObjectCounter()
{
	--count;
	nextID = currentObjectID;
}

unsigned ObjectCounter::getID() const
{
	return currentObjectID;
}
unsigned ObjectCounter::getObjectCount()
{
	return count;
}