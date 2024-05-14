#pragma once
#include <iostream>

class Animal
{
public:
	virtual void sayHello() const = 0;

	virtual Animal* clone()  const = 0;

	virtual ~Animal() = default;

	enum class AnimalType
	{
		Dog,
		Cat,
		Mouse
	};
};