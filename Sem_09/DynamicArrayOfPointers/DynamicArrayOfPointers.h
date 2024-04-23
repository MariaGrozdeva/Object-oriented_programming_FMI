#pragma once
#include <iostream>

struct A
{
	int x = 5;
	int y = 23;
};

class DynamicArrayOfPointers
{
public:
	DynamicArrayOfPointers();
	DynamicArrayOfPointers(const DynamicArrayOfPointers& other);
	DynamicArrayOfPointers(DynamicArrayOfPointers&& other) noexcept;
	
	DynamicArrayOfPointers& operator=(const DynamicArrayOfPointers& other);
	DynamicArrayOfPointers& operator=(DynamicArrayOfPointers&& other) noexcept;
	
	~DynamicArrayOfPointers();
	
	size_t size() const;

	void addAtFirstFreeIndex(const A& el);
	void addAtFirstFreeIndex(A&& el);
	
	void removeAt(unsigned index);
	void popBack();

	bool contains(unsigned index) const;

	void setAtIndex(const A& obj, unsigned index);
	void setAtIndex(A&& obj, unsigned index);

	const A& operator[](unsigned index) const;
	A& operator[](unsigned index);
	
private:
	A** data;
	size_t capacity;
	size_t count;

    	void copyFrom(const DynamicArrayOfPointers& other);
    	void moveFrom(DynamicArrayOfPointers&& other);
    
	void free();
	
	void resize(size_t newCapacity);

	int getFirstFreeIndex() const; // not optimal
};
