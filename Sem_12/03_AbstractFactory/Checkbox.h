#pragma once
#include <iostream>

class Checkbox
{
public:
	virtual void render() const = 0;
	virtual ~Checkbox() = default;
};
