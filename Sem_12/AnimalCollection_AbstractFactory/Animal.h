#pragma once
#include <iostream>
#include <string>

class Animal
{
public:
	virtual void sayHello() const = 0;
	virtual Animal* clone()  const = 0;
	virtual ~Animal() = default;
};

class AnimalCreator
{
public:
    	AnimalCreator(const std::string& animalName);
    	virtual ~AnimalCreator() = default;
    	const std::string& getAnimalName() const;

    	virtual Animal* createAnimal(std::istream& is) const = 0;

private:
    	std::string animalName;
};
