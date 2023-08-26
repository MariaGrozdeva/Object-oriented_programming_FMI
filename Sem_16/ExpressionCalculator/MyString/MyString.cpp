#include "MyString.h"
#include <cassert>
#include <iomanip>

void MyString::concat(const MyString& other)
{
	char* temp = new char[size + other.size + 1];
	strcpy(temp, str);
	strcat(temp, other.str);

	free();
	str = temp;
	size += other.size;
}

const char* MyString::c_str() const
{
	return str;
}
MyString MyString::substr(unsigned start, unsigned end) const
{
	if (end < start || end >= size)
	{
		throw std::logic_error("Invalid parameters");
	}

	MyString result;
	delete[] result.str;

	result.str = new char[end - start + 2];
	for (size_t i = start; i <= end; i++)
	{
		result.str[i - start] = str[i];
	}
	result.str[(end - start) + 1] = '\0';
	result.size = end - start + 1;

	return result;
}

size_t MyString::getSize() const
{
	return size;
}

char MyString::operator[](unsigned index) const
{
	assert(index < size);
	return str[index];
}
char& MyString::operator[](unsigned index)
{
	assert(index < size);
	return str[index];
}

MyString& MyString::operator+=(const MyString& other)
{
	concat(other);
	return *this;
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	os << str.str;
	return os;
}
std::istream& operator>>(std::istream& is, MyString& str)
{
	char buff[1024];
	is >> std::setw(1024) >> buff;
	size_t len = strlen(buff);
	
	delete[] str.str;
	str.str = new char[len + 1];
	strcpy(str.str, buff);

	return is;
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString lhsCopy(lhs);
	lhsCopy += rhs;
	return lhsCopy;
}

bool operator==(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}
bool operator<(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}
bool operator>(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

MyString::MyString(const char* str)
{
	if (str == nullptr || this->str == str)
	{
		return;
	}
	
	size_t len = strlen(str);
	this->str = new char[len + 1];
	strcpy(this->str, str);
	size = len;
}

MyString::MyString() : MyString("\0")
{}
MyString::MyString(const MyString& other)
{
	copyFrom(other);
}
MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
MyString::~MyString()
{
	free();
}

void MyString::copyFrom(const MyString& other)
{
	str = new char[strlen(other.str) + 1];
	strcpy(str, other.str);
	size = other.size;
}
void MyString::free()
{
	delete[] str;
}