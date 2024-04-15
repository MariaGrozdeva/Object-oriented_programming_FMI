#pragma once
#include <iostream>

class Set
{
public:
	Set(unsigned n);

	Set() = default;
	Set(const Set& other);
	Set& operator=(const Set& other);
	~Set();

	void add(unsigned num);
	void remove(unsigned num);
	bool contains(unsigned num) const; 
	void print() const;
	
	friend Set unionOfSets(const Set& lhs, const Set& rhs);
	friend Set intersectionOfSets(const Set& lhs, const Set& rhs);
	
private:
        unsigned n = 0;
	uint8_t* buckets = nullptr;
	size_t bucketsCount = 0;
	static constexpr size_t elementsInBucket = sizeof(uint8_t) * 8;
	
	unsigned getBucketIndex(unsigned num) const;
	unsigned getBitIndex(unsigned num) const;

        void copyFrom(const Set& other);
	void free();
};
