#include <algorithm>
#include "MyString.h"
#include "StringPool.h"

// Not algorithmically best. Used for educational purposes.

StringPool& StringPool::operator+=(const StringPool& other)
{
	for (size_t i = 0; i < other.count; i++)
		(*this) *= (*other.data[i]);
	return *this;
}
StringPool& StringPool::operator-=(const StringPool& other)
{
	for (size_t i = 0; i < other.count; i++)
		(*this) /= (*other.data[i]);
	return *this;
}

bool StringPool::operator[](const MyString& word) const
{
	return findWord(word) != -1;
}

StringPool& StringPool::operator*=(const MyString& word)
{
	if ((*this)[word])
		return *this;

	resize(count + 1);

	int currentStringPosition = count - 2;
	while (currentStringPosition >= 0 && *data[currentStringPosition] > word)
	{
		data[currentStringPosition + 1] = data[currentStringPosition];
		currentStringPosition--;
	}
	data[currentStringPosition + 1] = new MyString(word);

	return *this;
}
StringPool& StringPool::operator/=(const MyString& word)
{
	size_t indexOfWord = findWord(word);
	if (indexOfWord == -1)
		return *this;

	delete data[indexOfWord];

	for (size_t i = indexOfWord; i < count - 1; i++)
		data[i] = data[i + 1];

	resize(count - 1);

	return *this;
}

std::ostream& operator<<(std::ostream& os, const StringPool& pool)
{
	for (size_t i = 0; i < pool.count; i++)
		std::cout << *(pool.data[i]) << ' ';
	return os;
}
void operator>>(const MyString& word, StringPool& pool)
{
	pool *= word;
}

StringPool operator+(const StringPool& lhs, const StringPool& rhs)
{
	StringPool lhsCopy(lhs);
	lhsCopy += rhs;
	return lhsCopy;
}
StringPool operator-(const StringPool& lhs, const StringPool& rhs)
{
	StringPool lhsCopy(lhs);
	lhsCopy -= rhs;
	return lhsCopy;
}

StringPool::StringPool()
{
	data = nullptr;
	count = 0;
}
StringPool::StringPool(const StringPool& other)
{
	copyFrom(other);
}
StringPool& StringPool::operator=(const StringPool& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
StringPool::~StringPool()
{
	free();
}

void StringPool::copyFrom(const StringPool& other)
{
	count = other.count;
	data = new MyString * [count];
	for (size_t i = 0; i < count; i++)
		data[i] = new MyString(*other.data[i]);
}
void StringPool::free()
{
	for (size_t i = 0; i < count; i++)
		delete data[i];
	delete[] data;
}

void StringPool::resize(size_t newCount)
{
	MyString** resized = new MyString * [newCount];

	for (size_t i = 0; i < std::min(count, newCount); i++)
		resized[i] = data[i];
	count = newCount;

	delete[] data;
	data = resized;
}

int StringPool::findWord(const MyString& word) const
{
	int l = 0;
	int r = count - 1;

	while (l <= r)
	{
		size_t mid = l + (r - l) / 2;

		if (*data[mid] == word)
			return mid;
		else if (*data[mid] < word)
			l = mid + 1;
		else
			r = mid - 1;
	}

	return -1;
}
