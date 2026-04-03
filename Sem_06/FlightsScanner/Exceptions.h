#pragma once
#include <stdexcept>
#include <string>

class NullStringException : public std::invalid_argument
{
public:
    NullStringException() : std::invalid_argument("The given string does not exist") {}
};

class NonLetterCharException : public std::invalid_argument
{
public:
    NonLetterCharException(char ch) 
        : std::invalid_argument("Non-letter character found: '" + std::string(1, ch) + "'"), ch(ch) {}
    
    NonLetterCharException(char ch, const std::string& message)
        : std::invalid_argument(message), ch(ch) {}

    char getChar() const { return ch; }
private:
    char ch;
};

class NonDigitCharException : public std::invalid_argument
{
public:
    NonDigitCharException(char ch)
        : std::invalid_argument("Non-digit character found: '" + std::string(1, ch) + "'"), ch(ch) {}

    char getChar() const { return ch; }
private:
    char ch;
};
