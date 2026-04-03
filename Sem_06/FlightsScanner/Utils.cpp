#include "Utils.h"
#include "Exceptions.h"

bool isLower(char ch)
{
    return ch >= 'a' && ch <= 'z';
}

bool isLetter(char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

void toUpper(char* str)
{
    if (str == nullptr)
	{
        throw NullStringException();
	}

    constexpr int diff = 'a' - 'A';
    while (*str)
    {
        if (!isLetter(*str))
		{
            throw NonLetterCharException(*str);
		}
        if (isLower(*str))
		{
            *str = *str - diff;
		}
        str++;
    }
}

unsigned int charToDigit(char ch)
{
    if (ch < '0' || ch > '9')
	{
        throw NonDigitCharException(ch);
	}
    return ch - '0';
}

unsigned int strToNumber(const char* str)
{
    if (!str)
	{
        throw NullStringException();
	}

    unsigned int result = 0;
    while (*str)
    {
        result *= 10;
        result += charToDigit(*str);
        str++;
    }
    return result;
}
