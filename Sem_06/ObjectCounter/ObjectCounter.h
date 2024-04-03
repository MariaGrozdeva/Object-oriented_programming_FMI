#pragma once

class ObjectCounter
{
public:
	ObjectCounter();
	~ObjectCounter();

	unsigned getId() const;
	static unsigned getObjectCount();
	
private:
	unsigned currentObjectId;
        static unsigned nextId;
	const static unsigned Idstep = 1;
	
	static unsigned count;
};
