#pragma once

class ObjectCounter
{
private:
	size_t currentObjectID;

	static size_t count;
	static size_t nextID;
	const static size_t IDstep = 1;

public:
	ObjectCounter();
	~ObjectCounter();

	size_t getID() const;
	static size_t getObjectCount();
};