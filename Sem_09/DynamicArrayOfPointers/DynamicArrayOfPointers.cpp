#include "DynamicArrayOfPointers.h"
#include <stdexcept>

void DynamicArrayOfPointers::addAtFirstFreeIndex(const A& el)
{
    	if (count >= capacity)
	{
		resize(capacity * 2);
	}
	
	int index = getFirstFreeIndex();
	data[index] = new A(el);
	count++;
}

void DynamicArrayOfPointers::addAtFirstFreeIndex(A&& el)
{
	if (count >= capacity)
	{
		resize(capacity * 2);
	}
	
	int index = getFirstFreeIndex();
	data[index] = new A(std::move(el));
	count++;
}

int DynamicArrayOfPointers::getFirstFreeIndex() const
{
	for (size_t i = 0; i < capacity; i++)
	{
		if (!data[i])
		{
			return i;
		}
	}
	return -1; 
}

void DynamicArrayOfPointers::removeAt(unsigned index)
{
	if (index >= count)
    	{
        	throw std::out_of_range("Invalid index!");
    	}

	delete data[index];
	data[index] = nullptr;
	count--;

	// shrink if count is much smaller than capacity
}

void DynamicArrayOfPointers::popBack()
{
	if (size() == 0)
	{
		return;
	}

	delete data[count - 1];
	count--;
	
	// shrink if count is much smaller than capacity
}

bool DynamicArrayOfPointers::contains(unsigned index) const
{
	return index <= count && data[index];
}

void DynamicArrayOfPointers::setAtIndex(const A& obj, unsigned index)
{
	if (count >= capacity)
	{
		resize(capacity * 2);
	}
	
	if (data[index])
	{
		throw std::invalid_argument("An object at this index already exists");
	}

    	data[index] = new A(obj);
    	count++;
}

void DynamicArrayOfPointers::setAtIndex(A&& obj, unsigned index)
{
    	if (count >= capacity)
	{
		resize(capacity * 2);
	}
	
	if (data[index])
	{
		throw std::invalid_argument("An object at this index already exists");
	}

    	data[index] = new A(std::move(obj));
    	count++;
}

const A& DynamicArrayOfPointers::operator[](unsigned index) const
{
    	if (index >= count || !data[index])
    	{
        	throw std::out_of_range("Invalid index!");
    	}
	return *data[index];
}

A& DynamicArrayOfPointers::operator[](unsigned index)
{
	if (index >= count || !data[index])
    	{
        	throw std::out_of_range("Invalid index!");
    	}
	return *data[index];
}

size_t DynamicArrayOfPointers::size() const
{
	return count;
}

DynamicArrayOfPointers::DynamicArrayOfPointers()
{
	capacity = 8;
	count = 0;
	data = new A*[capacity]{ nullptr };
}

DynamicArrayOfPointers::DynamicArrayOfPointers(const DynamicArrayOfPointers& other)
{
	copyFrom(other);
}

DynamicArrayOfPointers::DynamicArrayOfPointers(DynamicArrayOfPointers&& other) noexcept
{
	moveFrom(std::move(other));
}

DynamicArrayOfPointers& DynamicArrayOfPointers::operator=(const DynamicArrayOfPointers& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

DynamicArrayOfPointers& DynamicArrayOfPointers::operator=(DynamicArrayOfPointers&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

DynamicArrayOfPointers::~DynamicArrayOfPointers()
{
	free();
}

void DynamicArrayOfPointers::copyFrom(const DynamicArrayOfPointers& other)
{
	count = other.count;
	capacity = other.capacity;
	
	data = new A*[capacity]{ nullptr };
	for (size_t i = 0; i < count; i++)
	{
		if (other.data[i])
		{
			data[i] = new A(*other.data[i]);
		}
	}
}

void DynamicArrayOfPointers::moveFrom(DynamicArrayOfPointers&& other)
{
	data = other.data;
	other.data = nullptr;
	capacity = other.capacity;
	count = other.count;
	other.capacity = other.count = 0; 
}

void DynamicArrayOfPointers::free()
{
	for (size_t i = 0; i < count; i++)
	{
		delete data[i];
	}
	delete[] data;
}

void DynamicArrayOfPointers::resize(size_t newCapacity)
{
	A** newData = new A*[newCapacity]{ nullptr };
	
	for (size_t i = 0; i < capacity; i++)
	{
		newData[i] = data[i];
	}

	delete[] data;
	data = newData;
	capacity = newCapacity;
}
