#pragma once
#include <iostream>
#include <cstring>
#include <stdexcept>

class SortedStringPool
{
private:
    static constexpr size_t maxStringSize = 64;

    struct String
    {
        char str[maxStringSize] = "";
        unsigned int refCount = 0;

        String(const char* s)
        {
            if (strlen(s) >= maxStringSize)
            {
                throw std::invalid_argument("String exceeds max size");
            }
            strcpy(str, s);
        }
    };

    size_t size = 0;
    size_t capacity = 4;
    String** data;

    void copyFrom(const SortedStringPool& other);
    void free();
    void resize(size_t newCapacity);
    size_t findInsertIndex(const char* str, bool& outFound, int& outExistingIndex) const;

public:
    SortedStringPool();
    SortedStringPool(const SortedStringPool& other);
    SortedStringPool& operator=(const SortedStringPool& other);
    ~SortedStringPool();

    bool add(const char* str);
    bool removeAt(unsigned int index);
    int contains(const char* str) const;
    const char* operator[](unsigned int index) const;

    friend std::ostream& operator<<(std::ostream& os, const SortedStringPool& pool);
};
