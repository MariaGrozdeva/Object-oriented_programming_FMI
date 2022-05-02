#pragma once

class StringPool
{
private:
	MyString** data;
	size_t count;

	void copyFrom(const StringPool& other);
	void free();

	void resize(size_t newCount);

	int findWord(const MyString& word) const;

public:
	StringPool();
	StringPool(const StringPool& other);
	StringPool& operator=(const StringPool& other);
	~StringPool();

	StringPool& operator+=(const StringPool& other);
	StringPool& operator-=(const StringPool& other);

	bool operator[](const MyString& word) const;

	StringPool& operator*=(const MyString& word);
	StringPool& operator/=(const MyString& word);

	friend std::ostream& operator<<(std::ostream& os, const StringPool& pool);
	friend void operator>>(const MyString& word, StringPool& pool);
};

StringPool operator+(const StringPool& lhs, const StringPool& rhs);
StringPool operator-(const StringPool& lhs, const StringPool& rhs);
