#include "MyString.h"

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
	os << str.str;
	return os;
}
std::istream& operator>>(std::istream& is, MyString& str)
{
	char buff[1024];
	is >> buff;
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
	std::cout << "Constructor" << std::endl;
	size_t len = strlen(str);
	this->str = new char[len + 1];
	strcpy(this->str, str);
	size = len;
}

MyString::MyString() : MyString("\0")
{}

MyString::MyString(const MyString& other)
{
	std::cout << "Copy constructor" << std::endl;
	copyFrom(other);
}
MyString::MyString(MyString&& other)
{
	std::cout << "Move constructor" << std::endl;
	move(std::move(other));
}

MyString& MyString::operator=(const MyString& other)
{
	std::cout << "Operator=" << std::endl;
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
MyString& MyString::operator=(MyString&& other)
{
	std::cout << "Move operator=" << std::endl;
	if (this != &other)
	{
		free();
		move(std::move(other));
	}
	return *this;
}

MyString::~MyString()
{
	std::cout << "Destructor" << std::endl;
	free();
}

void MyString::copyFrom(const MyString& other)
{
	str = new char[strlen(other.str) + 1];
	strcpy(str, other.str);
	size = other.size;
}
void MyString::move(MyString&& other)
{
	str = other.str;
	size = other.size;
	other.str = nullptr;
	other.size = 0;
}

void MyString::free()
{
	delete[] str;
}