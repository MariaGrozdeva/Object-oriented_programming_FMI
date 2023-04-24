#pragma once
#pragma warning (disable : 4996)

class MyString
{
private:
	char* str;
	size_t size;

	void copyFrom(const MyString& other);
	void free();

public:
	MyString(const char* str);

	MyString();
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
