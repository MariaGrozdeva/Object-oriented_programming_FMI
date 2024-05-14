#pragma once
#include "Animal.h"

class Cat : public Animal
{
public:
	virtual void sayHello() const override;
	virtual Animal* clone() const override;
};