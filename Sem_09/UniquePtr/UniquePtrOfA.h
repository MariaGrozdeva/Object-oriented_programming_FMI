#pragma once

struct A
{
	int a = 5;
	int b = 23;
};

class UniquePtrOfA
{
public:
	UniquePtrOfA(A* ptr);

	UniquePtrOfA(const UniquePtrOfA&) = delete;
	UniquePtrOfA& operator=(const UniquePtrOfA&) = delete;

	UniquePtrOfA(UniquePtrOfA&&) noexcept;
	UniquePtrOfA& operator=(UniquePtrOfA&&) noexcept;
	
	~UniquePtrOfA();

	A& operator*();
	const A& operator*() const;
	
	A* operator->();
	const A* operator->() const;
	
private:
	A* ptr;
};