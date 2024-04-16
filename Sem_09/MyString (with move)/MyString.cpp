#include "MyString.h"
#include <cstring>
#include <iomanip>
#include <stdexcept>

#pragma warning (disable : 4996)

void MyString::concat(const MyString& other)
{
	if (!str || !other.str)
    	{
        	throw std::logic_error("Null strings can't be concatenated");
    	}
	
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

size_t MyString::getSize() const
{
	return size;
}

MyString& MyString::operator+=(const MyString& other)
{
	concat(other);
	return *this;
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	return os << str.str;
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
	if (!lhs.c_str() || !rhs.c_str())
    	{
        	throw std::logic_error("Null strings can't be compared");
    	}
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}
bool operator<(const MyString& lhs, const MyString& rhs)
{
   	if (!lhs.c_str() || !rhs.c_str())
    	{
        	throw std::logic_error("Null strings can't be compared");
    	}
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}
bool operator>(const MyString& lhs, const MyString& rhs)
{
    	if (!lhs.c_str() || !rhs.c_str())
    	{
        	throw std::logic_error("Null strings can't be compared");
    	}
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

MyString::MyString(const char* str)
{
	if (str == nullptr || this->str == str)
	{
		throw std::invalid_argument("Invalid parameter!");
	}
	
	size_t len = strlen(str);
	this->str = new char[len + 1];
	strcpy(this->str, str);
	size = len;
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}
MyString::MyString(MyString&& other) noexcept
{
	moveFrom(std::move(other));
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
MyString& MyString::operator=(MyString&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
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
void MyString::moveFrom(MyString&& other)
{
	str = other.str;
	size = other.size;
	other.str = nullptr;
	other.size = 0;
}

void MyString::free()
{
	delete[] str;
	str = nullptr;
	size = 0;
}