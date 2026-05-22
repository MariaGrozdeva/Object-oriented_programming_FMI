#pragma once
#include <iostream>

class MyString
{
private:
	char* str = nullptr;
	size_t size = 0;

	void copyFrom(const MyString& other);
	void free();

public:
	MyString(const char* str);

	MyString() = default;
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);
	~MyString();

	void concat(const MyString& other);
	
	const char* c_str() const;

	size_t getSize() const;

	MyString& operator+=(const MyString& other);

	friend std::ostream& operator<<(std::ostream& os, const MyString& str);
	friend std::istream& operator>>(std::istream& is, MyString& str);
};

MyString operator+(const MyString& lhs, const MyString& rhs);

bool operator==(const MyString& lhs, const MyString& rhs);
bool operator<(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
