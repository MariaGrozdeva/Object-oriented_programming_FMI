#include "DynamicArrayOfPointers.h"
#include <stdexcept>
#include <utility>

DynamicArrayOfPointers::DynamicArrayOfPointers()
{
	capacity = 8;
	count = 0;
	data = new A*[capacity]{nullptr};
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
		DynamicArrayOfPointers tmp(other);
		free();
		moveFrom(std::move(tmp));
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

size_t DynamicArrayOfPointers::size() const
{
	return count;
}

void DynamicArrayOfPointers::addAtFirstFreeIndex(const A& el)
{
	if (count >= capacity)
	{
		resize(capacity * 2);
	}
	int index = getFirstFreeIndex();
	A* newEl = new A(el);
	data[index] = newEl;
	count++;
}

void DynamicArrayOfPointers::addAtFirstFreeIndex(A&& el)
{
	if (count >= capacity)
	{
		resize(capacity * 2);
	}
	int index = getFirstFreeIndex();
	A* newEl = new A(std::move(el));
	data[index] = newEl;
	count++;
}

void DynamicArrayOfPointers::removeAt(unsigned index)
{
	if (index >= capacity)
	{
		throw std::out_of_range("Invalid index!");
	}
	if (data[index])
	{
		delete data[index];
		data[index] = nullptr;
		count--;
	}
}

bool DynamicArrayOfPointers::contains(unsigned index) const
{
	return index < capacity && data[index];
}

void DynamicArrayOfPointers::setAtIndex(const A& obj, unsigned index)
{
	if (index >= capacity)
	{
		resize(index * 2 + 1);
	}
	if (data[index])
	{
		throw std::invalid_argument("An object at this index already exists");
	}
	A* newEl = new A(obj);
	data[index] = newEl;
	count++;
}

void DynamicArrayOfPointers::setAtIndex(A&& obj, unsigned index)
{
	if (index >= capacity)
	{
		resize(index * 2 + 1);
	}
	if (data[index])
	{
		throw std::invalid_argument("An object at this index already exists");
	}
	A* newEl = new A(std::move(obj));
	data[index] = newEl;
	count++;
}

const A& DynamicArrayOfPointers::operator[](unsigned index) const
{
	if (index >= capacity || !data[index])
	{
		throw std::out_of_range("Invalid index");
	}
	return *data[index];
}

A& DynamicArrayOfPointers::operator[](unsigned index)
{
	if (index >= capacity || !data[index])
	{
		throw std::out_of_range("Invalid index");
	}
	return *data[index];
}

void DynamicArrayOfPointers::copyFrom(const DynamicArrayOfPointers& other)
{
	A** newData = new A*[other.capacity]{nullptr};
	size_t i = 0;
	try
	{
		for (; i < other.capacity; i++)
		{
			if (other.data[i])
			{
				newData[i] = new A(*other.data[i]);
			}
		}
	}
	catch (...)
	{
		for (size_t j = 0; j < i; j++)
		{
			delete newData[j];
		}
		delete[] newData;
		throw;
	}

	data = newData;
	capacity = other.capacity;
	count = other.count;
}

void DynamicArrayOfPointers::moveFrom(DynamicArrayOfPointers&& other) noexcept
{
	data = other.data;
	capacity = other.capacity;
	count = other.count;
	other.data = nullptr;
	other.capacity = 0;
	other.count = 0;
}

void DynamicArrayOfPointers::free() noexcept
{
	for (size_t i = 0; i < capacity; i++)
	{
		delete data[i];
	}
	delete[] data;
	data = nullptr;
	capacity = 0;
	count = 0;
}

void DynamicArrayOfPointers::resize(size_t newCapacity)
{
	A** newData = new A*[newCapacity]{nullptr};
	for (size_t i = 0; i < capacity; i++)
	{
		newData[i] = data[i];
	}
	delete[] data;
	data = newData;
	capacity = newCapacity;
}

int DynamicArrayOfPointers::getFirstFreeIndex() const
{
	for (size_t i = 0; i < capacity; i++)
	{
		if (!data[i])
		{
			return static_cast<int>(i);
		}
	}
	return -1;
}
