#pragma once
#include <iostream>

template <typename T1, typename T2>
class Pair
{
private:
	T1 first;
	T2 second;

public:
	Pair() = default;
	Pair(const T1& first, const T2& second);

	void setFirst(const T1& first);
	void setSecond(const T2& second);
	
	const T1& getFirst() const;
	const T2& getSecond() const;
};

template <typename T1, typename T2>
Pair<T1, T2>::Pair(const T1& first, const T2& second) : first(first), second(second)
{}

template <typename T1, typename T2>
void Pair<T1, T2>::setFirst(const T1& first)
{
	this->first = first;
}
template <typename T1, typename T2>
void Pair<T1, T2>::setSecond(const T2& second)
{
	this->second = second;
}

template <typename T1, typename T2>
const T1& Pair<T1, T2>::getFirst() const
{
	return first;
}
template <typename T1, typename T2>
const T2& Pair<T1, T2>::getSecond() const
{
	return second;
}
