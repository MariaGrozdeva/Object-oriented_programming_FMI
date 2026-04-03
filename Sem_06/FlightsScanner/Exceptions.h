#pragma once
#include <stdexcept>
#include <string>

class NullStringException
{
public:
    NullStringException() {}
};

class NonLetterCharException
{
public:
    NonLetterCharException(char ch) : ch(ch) {}
    
    NonLetterCharException(char ch, const std::string& message)
        : ch(ch) {}
    
    char getChar() const { return ch; }
private:
    char ch;
};

class NonDigitCharException
{
public:
    NonDigitCharException(char ch) : ch(ch) {}
    char getChar() const { return ch; }
private:
    char ch;
};
