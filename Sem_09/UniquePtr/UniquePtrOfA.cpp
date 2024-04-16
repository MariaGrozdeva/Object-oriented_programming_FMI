#include "UniquePtrOfA.h"

UniquePtrOfA::UniquePtrOfA(A* ptr) : ptr(ptr)
{}

UniquePtrOfA::UniquePtrOfA(UniquePtrOfA&& other) noexcept
{
	ptr = other.ptr;
	other.ptr = nullptr;
}

UniquePtrOfA& UniquePtrOfA::operator=(UniquePtrOfA&& other) noexcept
{
	if (this != &other)
	{
		delete ptr;
		ptr = other.ptr;
		other.ptr = nullptr;
	}
	return *this;
}

UniquePtrOfA::~UniquePtrOfA()
{
	delete ptr;
}

A& UniquePtrOfA::operator*()
{
	return *ptr;
}

const A& UniquePtrOfA::operator*() const
{
	return *ptr;
}

A* UniquePtrOfA::operator->()
{
	return ptr;
}

const A* UniquePtrOfA::operator->() const
{
	return ptr;
}
