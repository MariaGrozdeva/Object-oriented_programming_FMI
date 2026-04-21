#pragma once
#include <iostream>

class MyString
{
private:
    char* str = nullptr;
    size_t size = 0;

public:
    MyString() = default;
    explicit MyString(const char* str);
    MyString(const MyString& other);
    MyString& operator=(const MyString& other);
    ~MyString() noexcept;

    const char* c_str() const noexcept;
    size_t getSize() const noexcept;
    
    MyString& operator+=(const MyString& other);
    
    friend void swap(MyString& lhs, MyString& rhs) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const MyString& s);
    friend std::istream& operator>>(std::istream& is, MyString& s);
};

MyString operator+(const MyString& lhs, const MyString& rhs);

bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);
bool operator< (const MyString& lhs, const MyString& rhs);
bool operator> (const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);
