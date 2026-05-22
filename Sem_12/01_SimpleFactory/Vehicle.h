#pragma once
#include <iostream>

class Vehicle
{
public:
	virtual void describe() const = 0;
	virtual ~Vehicle() = default;
};
