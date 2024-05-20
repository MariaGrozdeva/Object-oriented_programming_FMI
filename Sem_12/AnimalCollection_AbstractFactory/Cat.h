#pragma once
#include "Animal.h"

class Cat : public Animal
{
public:
	virtual void sayHello() const override;
	virtual Animal* clone() const override;
};

class CatCreator : public AnimalCreator
{
public :
    	CatCreator();
    	virtual Animal* createAnimal(std::istream& is) const override;
};
