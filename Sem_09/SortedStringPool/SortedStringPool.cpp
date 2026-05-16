#include "SortedStringPool.h"
#include <cassert>

size_t SortedStringPool::findInsertIndex(const char* str, bool& outFound, int& outExistingIndex) const
{
    outFound = false;
    outExistingIndex = -1;

    int low = 0;
    int high = static_cast<int>(size) - 1;
    size_t insertAt = size; // default: append at end

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        int cmp = strcmp(str, data[mid]->str);

        if (cmp == 0)
        {
            outFound = true;
            outExistingIndex = mid;
            insertAt = static_cast<size_t>(mid);
            high = mid - 1;
        }
        else if (cmp < 0)
        {
            insertAt = static_cast<size_t>(mid);
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return insertAt;
}

void SortedStringPool::resize(size_t newCapacity)
{
    String** resized = new String*[newCapacity]();

    for (size_t i = 0; i < size; i++)
    {
        resized[i] = data[i];
    }

    delete[] data;
    data = resized;
    capacity = newCapacity;
}

void SortedStringPool::copyFrom(const SortedStringPool& other)
{
    capacity = other.capacity;
    size = 0;
    data = new String*[capacity]();

    for (size_t i = 0; i < other.size; i++)
    {
        if (i > 0 && other.data[i] == other.data[i - 1])
        {
            data[i] = data[i - 1];
        }
        else
        {
            // May throw — size has not been bumped yet, so the destructor
            // will only see fully constructed slots.
            data[i] = new String(*other.data[i]);
        }

        data[i]->refCount++;
        size++; // bump only after the slot is fully initialised
    }
}

void SortedStringPool::free()
{
    for (size_t i = 0; i < size; i++)
    {
        if (data[i]->refCount == 1)
        {
            delete data[i];
        }
        else
        {
            data[i]->refCount--;
        }
    }

    delete[] data;
    data = nullptr;
}

SortedStringPool::SortedStringPool() : size(0), capacity(4), data(new String*[capacity]())
{}

SortedStringPool::SortedStringPool(const SortedStringPool& other)
{
    copyFrom(other);
}

SortedStringPool& SortedStringPool::operator=(const SortedStringPool& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

SortedStringPool::~SortedStringPool()
{
    free();
}

bool SortedStringPool::add(const char* str)
{
    if (strlen(str) >= maxStringSize)
    {
        return false;
    }

    bool found = false;
    int existingIndex = -1;
    size_t insertAt = findInsertIndex(str, found, existingIndex);

    if (size == capacity)
    {
        resize(capacity * 2);
    }

    String* node = found ? data[existingIndex] : new String(str);
    for (size_t i = size; i > insertAt; i--)
    {
        data[i] = data[i - 1];
    }

    data[insertAt] = node;
    node->refCount++;
    size++;

    return true;
}

bool SortedStringPool::removeAt(unsigned int index)
{
    if (index >= size)
    {
        return false;
    }

    if (data[index]->refCount == 1)
    {
        delete data[index];
    }
    else
    {
        data[index]->refCount--;
    }

    size--;

    for (size_t i = index; i < size; i++)
    {
        data[i] = data[i + 1];
    }

    return true;
}

int SortedStringPool::contains(const char* str) const
{
	bool found = false;
    int existingIndex = -1;
    findInsertIndex(str, found, existingIndex);
    return found ? existingIndex : -1;
}

const char* SortedStringPool::operator[](unsigned int index) const
{
    assert(index < size);
    return data[index]->str;
}

std::ostream& operator<<(std::ostream& os, const SortedStringPool& pool)
{
    for (size_t i = 0; i < pool.size; i++)
    {
        os << pool[i] << ' ';
    }
    return os;
}
