#pragma once
#include <iostream>

class Animal
{
public:
	virtual void sayHello() const = 0;

	virtual Animal* clone()  const = 0; // creates a copy of the current object

	virtual ~Animal() 
	{}

	enum class AnimalType
	{
		Dog,
		Cat,
		Mouse
	};
};