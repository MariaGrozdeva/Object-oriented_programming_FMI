#pragma once
#include "Animal.h"

class Dog : public Animal
{
public:
	virtual void sayHello() const override;
	virtual Animal* clone() const override;
};