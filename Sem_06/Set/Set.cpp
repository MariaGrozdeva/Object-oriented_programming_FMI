#include "Set.h"

Set::Set(unsigned n)
{
	bucketsCount = n / elementsInBucket + 1;
	buckets = new uint8_t[bucketsCount]{ 0 };
	this->n = n;
}

Set::Set(const Set& other)
{
	copyFrom(other);
}

Set& Set::operator=(const Set& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Set::~Set()
{
	free();
}

void Set::add(unsigned num)
{
	if (num > n)
	{
		return;
	}

	unsigned bucketIndex = getBucketIndex(num);
	unsigned bitIndex = getBitIndex(num);

	uint8_t mask = 1 << bitIndex; 
	buckets[bucketIndex] |= mask;
}

void Set::remove(unsigned num)
{
        if (num > n)
	{
		return;
	}
	
	unsigned bucketIndex = getBucketIndex(num);
	unsigned bitIndex = getBitIndex(num);

	uint8_t mask = ~(1 << bitIndex);
	buckets[bucketIndex] &= mask; 
}

bool Set::contains(unsigned num) const
{
        if (num > n)
	{
		return false;
	}
	
	unsigned bucketIndex = getBucketIndex(num);
	unsigned bitIndex = getBitIndex(num);

	uint8_t mask = 1 << bitIndex;
	return buckets[bucketIndex] & mask;
}

void Set::print() const
{
	std::cout << "{ ";
	for (size_t i = 0; i < n; i++)
	{
		if (contains(i))
		{
			std::cout << i << " ";
		}
	}
	std::cout << "}" << std::endl;
}

Set unionOfSets(const Set& lhs, const Set& rhs)
{
	Set result(std::max(lhs.n, rhs.n));

	size_t minBucketsCount = std::min(lhs.bucketsCount, rhs.bucketsCount);
	for (size_t i = 0; i < minBucketsCount; i++)
	{
		result.buckets[i] = lhs.buckets[i] | rhs.buckets[i];
	}

	const Set& biggerSet = lhs.bucketsCount > rhs.bucketsCount ? lhs : rhs;
	for (size_t i = minBucketsCount; i < biggerSet.bucketsCount; i++)
	{
		result.buckets[i] = biggerSet.buckets[i];
	}
		
	return result;
}

Set intersectionOfSets(const Set& lhs, const Set& rhs)
{
	Set result(std::min(lhs.n, rhs.n));

	size_t minBucketsCount = std::min(lhs.bucketsCount, rhs.bucketsCount);
	for (size_t i = 0; i < minBucketsCount; i++)
	{
		result.buckets[i] = lhs.buckets[i] & rhs.buckets[i];
	}
	
	return result;
}

unsigned Set::getBucketIndex(unsigned num) const
{
	return num / elementsInBucket;
}

unsigned Set::getBitIndex(unsigned num) const
{
	return num % elementsInBucket;
}

void Set::copyFrom(const Set& other)
{
	buckets = new uint8_t[other.bucketsCount];
	for (size_t i = 0; i < other.bucketsCount; i++)
	{
		buckets[i] = other.buckets[i];
	}
	bucketsCount = other.bucketsCount;
	n = other.n;
}

void Set::free()
{
	delete[] buckets;
	buckets = nullptr;
	bucketsCount = 0;
}
