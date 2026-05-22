#pragma once
#include <iostream>

class Button
{
public:
	virtual void render() const = 0;
	virtual ~Button() = default;
};
