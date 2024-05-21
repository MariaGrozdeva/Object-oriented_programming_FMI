#pragma once
#include "Animal.h"

class Snake : public Animal
{
public:
    	Snake(size_t length, bool isVenomous );
	virtual void sayHello() const override;
	virtual Animal* clone() const override;
	
	size_t getSnakeLength() const;
	bool getIsVenomous() const;
	
private:
    	size_t length;
    	bool isVenomous;
};

class SnakeCreator : public AnimalCreator
{
public :
    	SnakeCreator();
    	virtual Animal* createAnimal(std::istream& is) const override;
};
