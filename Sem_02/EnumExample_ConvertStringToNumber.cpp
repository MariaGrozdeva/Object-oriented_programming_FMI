#include <iostream>

enum class ErrorCode
{
    OK,
    InvalidSymbol,
    EmptyString,
    NullptrGiven
};

struct ConvertResult
{
    ErrorCode errorCode;
    unsigned result;
};

bool isDigit(char ch)
{ 
    return ch >= '0' && ch <= '9';
}
unsigned short convertCharToDigit(char ch)
{
    return ch - '0';
}

ConvertResult convertStringToNumber(const char* str)
{
    if (!str)
    {
        return { ErrorCode::NullptrGiven, 0 };
    }

    if (*str == '\0')
    {
        return { ErrorCode::EmptyString, 0 };
    }

    unsigned num = 0;
    while (*str)
    {
        if (!isDigit(*str))
        {
            return { ErrorCode::InvalidSymbol, 0 };
        }
        (num *= 10) += convertCharToDigit(*str); 
        str++;
    }
    
    return { ErrorCode::OK, num };
}

int main()
{
    ConvertResult convertedNum = convertStringToNumber("12343");
    
    if (convertedNum.errorCode == ErrorCode::OK)
    {
        std::cout << convertedNum.result << std::endl;
    }
    else
    {
        std::cout << "Error!" << std::endl;
    }
}
