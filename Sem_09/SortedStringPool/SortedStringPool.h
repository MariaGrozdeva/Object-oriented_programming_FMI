#pragma once
#include <iostream>
#include <cstring>

#pragma warning (disable : 4996)

class SortedStringPool
{
private:
	const static size_t maxStringSize = 64;
	struct String
	{
		char str[maxStringSize] = "";
		unsigned int refCount = 0;

		String(const char* str)
		{
			if (strlen(str) > maxStringSize)
			{
				throw std::invalid_argument("The length of the argument is longer than the max size");
			}
			strcpy(this->str, str);
		}
	};

	String** data;
	size_t size = 0;
	size_t capacity = 4;

	void copyFrom(const SortedStringPool& other);
	void free();

	void resize(size_t newCapacity);

public:
	SortedStringPool();
	SortedStringPool(const SortedStringPool& other);
	SortedStringPool& operator=(const SortedStringPool& other);
	~SortedStringPool();

	bool add(const char* str);
	bool removeAt(unsigned int index);
	int contains(const char* str) const; // returns the index of the first occurrence of str or -1 if it doesn't exist

	const char* operator[](unsigned int index) const;
	
	friend std::ostream& operator<<(std::ostream& os, const SortedStringPool& pool);
};