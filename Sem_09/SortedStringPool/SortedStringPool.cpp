#include "SortedStringPool.h"
#include <cassert>

bool SortedStringPool::add(const char* str)
{
	if (strlen(str) >= maxStringSize)
	{
		return false;
	}

	if (size == capacity)
	{
		resize(capacity * 2);
	}

	int currentIndex = size - 1;
	int lastStrcmpRes = -1;
	while (currentIndex >= 0 && ((lastStrcmpRes = strcmp(str, (*this)[currentIndex])) < 0))
	{
		data[currentIndex + 1] = data[currentIndex];
		currentIndex--;
	}

	if (currentIndex + 1 > 0 && lastStrcmpRes == 0)
	{
		data[currentIndex + 1] = data[currentIndex];
	}
	else
	{
		data[currentIndex + 1] = new String(str);
	}
	data[currentIndex + 1]->refCount++;

	size++;
	return true;
}
bool SortedStringPool::removeAt(unsigned int index)
{
	if (index >= size)
	{
		return false;
	}

	if (data[index]->refCount == 1)
	{
		delete data[index];
	}
	else
	{
		data[index]->refCount--;
	}

	size--;
	for (size_t i = index; i < size; i++)
	{
		data[i] = data[i + 1];
	}
	return true;
}
int SortedStringPool::contains(const char* str) const
{
	int start = 0, end = size - 1;
	int result = -1;

	while (start <= end)
	{
		unsigned int mid = start + (end - start) / 2;
		int strcmpRes = strcmp(str, (*this)[mid]);

		if (strcmpRes == 0)
		{
			end = mid - 1;
			result = mid;
		}
		else if (strcmpRes < 0)
		{
			end = mid - 1;
		}
		else
		{
			start = mid + 1;
		}
	}
	return result;
}

const char* SortedStringPool::operator[](unsigned int index) const
{
	assert(index < size);
	return data[index]->str;
}

std::ostream& operator<<(std::ostream& os, const SortedStringPool& pool)
{
	for (size_t i = 0; i < pool.size; i++)
	{
		os << pool[i] << ' ';
	}
	return os;
}

SortedStringPool::SortedStringPool()
{
	data = new String * [capacity] {nullptr};
}
SortedStringPool::SortedStringPool(const SortedStringPool& other)
{
	copyFrom(other);
}
SortedStringPool& SortedStringPool::operator=(const SortedStringPool& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
SortedStringPool::~SortedStringPool()
{
	free();
}

void SortedStringPool::copyFrom(const SortedStringPool& other)
{
	size = other.size;
	capacity = other.capacity;

	data = new String * [capacity] {nullptr};
	for (size_t i = 0; i < size; i++)
	{
		if (i != 0 && other.data[i] == other.data[i - 1])
		{
			data[i] = data[i - 1];
		}
		else
		{
			data[i] = new String(*other.data[i]);
		}
		data[i]->refCount++;
	}
}
void SortedStringPool::free()
{
	for (size_t i = 0; i < size; i++)
	{
		if (data[i]->refCount == 1)
		{
			delete data[i];
		}
		else
		{
			data[i]->refCount--;
		}
	}
	delete[] data;
}

void SortedStringPool::resize(size_t newCapacity)
{
	capacity = newCapacity;
	String** resized = new String * [capacity] {nullptr};

	for (size_t i = 0; i < size; i++)
	{
		resized[i] = data[i];
	}
	delete[] data;
	data = resized;
}