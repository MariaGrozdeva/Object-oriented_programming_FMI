#include "StringView.h"
#include <cstring>
#include <stdexcept>

StringView::StringView(const char* begin, const char* end) : begin(begin), end(end)
{}

StringView::StringView(const char* str) : StringView(str, str + strlen(str))
{}

StringView::StringView(const MyString& str) : StringView(str.c_str())
{}

size_t StringView::length() const
{
	return end - begin;
}

char StringView::operator[](size_t index) const
{
	return begin[index];
}

StringView StringView::substr(size_t from, size_t length) const
{
	if (begin + from + length > end)
	{
		throw std::length_error("Error: Substr out of range");
	}
	return StringView(begin + from, begin + from + length);
}

std::ostream& operator<<(std::ostream& os, const StringView& strView)
{
	const char* iter = strView.begin;
	while (iter != strView.end)
	{
		os << *iter;
		iter++;
	}
	return os;
}

bool operator==(const StringView& lhs, const StringView& rhs)
{
	if (lhs.length() != rhs.length())
	{
		return false;
	}
	
	for (size_t i = 0; i < lhs.length(); i++)
	{
		if (lhs[i] != rhs[i])
		{
			return false;
		}
	}
	return true;
}

bool operator!=(const StringView& lhs, const StringView& rhs)
{
	return !operator==(lhs, rhs);
}
