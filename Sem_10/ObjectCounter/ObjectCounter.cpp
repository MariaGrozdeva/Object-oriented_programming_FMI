#include <iostream>
#include "ObjectCounter.h"

size_t ObjectCounter::count = 0;
size_t ObjectCounter::nextID = 0;

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

size_t ObjectCounter::getID() const
{
	return currentObjectID;
}
size_t ObjectCounter::getObjectCount()
{
	return count;
}