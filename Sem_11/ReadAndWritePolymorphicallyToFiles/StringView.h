#pragma once
#include <fstream>
#include "MyString.h"

class StringView
{
public:
	StringView() = default;
	StringView(const char* begin, const char* end);
	StringView(const char* str);
	StringView(const MyString& string);

	size_t length() const;
	
	char operator[](size_t ind) const;

	StringView substr(size_t from, size_t length) const;
	
	friend std::ostream& operator<<(std::ostream&, const StringView& strView);
	
private:
	const char* begin = nullptr;
	const char* end = nullptr; // one pos after the last char
};

bool operator==(const StringView& lhs, const StringView& rhs);
bool operator!=(const StringView& lhs, const StringView& rhs);