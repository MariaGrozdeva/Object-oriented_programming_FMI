#pragma once

class ObjectCounter
{
public:
	ObjectCounter();
	~ObjectCounter();

 	ObjectCounter(const ObjectCounter&) = delete;
    ObjectCounter& operator=(const ObjectCounter&) = delete;

	unsigned getId() const;
	static unsigned getObjectCount();
	
private:
	unsigned currentObjectId;
    static unsigned nextId;
	constexpr static unsigned idStep = 1;
	
	static unsigned count;
};
