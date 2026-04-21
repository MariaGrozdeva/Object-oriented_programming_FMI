#include "MyString.h"
#include <cstring>
#include <iomanip>
#include <stdexcept>

void swap(MyString& lhs, MyString& rhs) noexcept
{
    using std::swap;
    swap(lhs.str,  rhs.str);
    swap(lhs.size, rhs.size);
}

MyString::MyString(const char* src)
{
    if (src == nullptr)
    {
        throw std::invalid_argument("MyString: null pointer passed to constructor");
    }

    size_t len = std::strlen(src);
    str  = new char[len + 1];
    std::memcpy(str, src, len + 1);
    size = len;
}

MyString::MyString(const MyString& other)
{
    if (other.str == nullptr)
    {
        return;
    }

    str  = new char[other.size + 1];
    std::memcpy(str, other.str, other.size + 1);
    size = other.size;
}

// Copy-and-swap: construct a copy of 'other' into 'tmp'.
// If new throws inside the copy ctor, *this is never touched.
// Once we have a valid tmp, swap is noexcept — no way to half-commit.
// The old resources are freed when tmp destructs at end of scope.
MyString& MyString::operator=(const MyString& other)
{
    if (this != &other)
    {
        MyString tmp(other);
        swap(*this, tmp);
    }
    return *this;
}

MyString::~MyString() noexcept
{
    delete[] str;
}

const char* MyString::c_str() const noexcept
{
    return str;
}

size_t MyString::getSize() const noexcept
{
    return size;
}

MyString& MyString::operator+=(const MyString& other)
{
    if (other.str == nullptr)
    {
        return *this;
    }

    if (str == nullptr)
    {
        MyString tmp(other);
        swap(*this, tmp);
        return *this;
    }

    // Allocate full combined buffer BEFORE touching *this.
    // If new throws, *this is still intact.
    size_t newSize = size + other.size;
    char* buf = new char[newSize + 1];
    std::memcpy(buf, str, size);
    std::memcpy(buf + size, other.str, other.size + 1);

    // No-throw commit from here
    delete[] str;
    str = buf;
    size = newSize;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const MyString& s)
{
    if (s.str)
    {
        os << s.str;
    }
    return os;
}

std::istream& operator>>(std::istream& is, MyString& s)
{
    char buff[1024];
    if (is >> std::setw(1024) >> buff)
    {
        MyString tmp(buff);
        swap(s, tmp);
    }
    return is;
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
    MyString tmp(lhs);
    tmp += rhs;
    return tmp;
}

static int safeStrcmp(const MyString& lhs, const MyString& rhs)
{
    if (!lhs.c_str() || !rhs.c_str())
    {
        throw std::logic_error("MyString: cannot compare null strings");
    }
    return std::strcmp(lhs.c_str(), rhs.c_str());
}

bool operator==(const MyString& lhs, const MyString& rhs) { return safeStrcmp(lhs, rhs) == 0; }
bool operator!=(const MyString& lhs, const MyString& rhs) { return !(lhs == rhs); }
bool operator< (const MyString& lhs, const MyString& rhs) { return safeStrcmp(lhs, rhs) <  0; }
bool operator> (const MyString& lhs, const MyString& rhs) { return rhs < lhs; }
bool operator<=(const MyString& lhs, const MyString& rhs) { return !(rhs < lhs); }
bool operator>=(const MyString& lhs, const MyString& rhs) { return !(lhs < rhs); }
