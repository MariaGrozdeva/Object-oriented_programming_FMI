#include "ObjectCounter.h"

unsigned ObjectCounter::nextId = 1;
unsigned ObjectCounter::count = 0;

ObjectCounter::ObjectCounter()
{
	++count;
	currentObjectId = nextId;
	nextId += Idstep;
}
ObjectCounter::~ObjectCounter()
{
	--count;
}

unsigned ObjectCounter::getId() const
{
	return currentObjectId;
}
unsigned ObjectCounter::getObjectCount()
{
	return count;
}
