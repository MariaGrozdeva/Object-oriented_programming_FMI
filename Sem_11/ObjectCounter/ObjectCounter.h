#pragma once

class ObjectCounter
{
private:
	unsigned currentObjectID;

	static unsigned count;
	static unsigned nextID;
	const static unsigned IDstep = 1;

public:
	ObjectCounter();
	~ObjectCounter();

	unsigned getID() const;
	static unsigned getObjectCount();
};