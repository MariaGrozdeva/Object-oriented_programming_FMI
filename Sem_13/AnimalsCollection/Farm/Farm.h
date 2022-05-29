#pragma once
#include "Animal.h"

class Farm
{
private:
	Animal** animals;
	size_t capacity;
	size_t count;

	void free();
	void copyFrom(const Farm& other);

	void resize();

public:
	Farm();
	Farm(const Farm& other);
	Farm& operator=(const Farm& other);
	~Farm();

	void addAnimal(const Animal& animal);

	void allSayHello() const;
};