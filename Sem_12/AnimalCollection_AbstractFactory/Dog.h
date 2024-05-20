#pragma once
#include "Animal.h"
#include <string>

class Dog : public Animal
{
public:
    	Dog(const std::string& breed);
	virtual void sayHello() const override;
	virtual Animal* clone() const override;
	
	const std::string& getBreed() const;
	
private:
    	std::string breed;
};

class DogCreator : public AnimalCreator
{
public :
    	DogCreator();
    	virtual Animal* createAnimal(std::istream& is) const override;
};
