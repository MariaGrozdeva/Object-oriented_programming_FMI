#pragma once
#include <iostream>

template <typename T, typename P>
class Pair
{
private:
	T first;
	P second;

public:
	Pair() = default;
	Pair(const T& first, const T& second);

	const T& getFirst() const;
	const T& getSecond() const;
};

template <typename T, typename P>
Pair<T, P>::Pair(const T& first, const T& second) : first(first), second(second)
{}

template <typename T, typename P>
const T& Pair<T, P>::getFirst() const
{
	return first;
}
template <typename T, typename P>
const T& Pair<T, P>::getSecond() const
{
	return second;
}