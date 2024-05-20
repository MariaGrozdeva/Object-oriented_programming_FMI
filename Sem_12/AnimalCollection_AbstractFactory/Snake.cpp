#include "Snake.h"

Snake::Snake(size_t length, bool isVenomous) : length(length), isVenomous(isVenomous)
{}

void Snake::sayHello() const 
{
	std::cout << "Hello, I am a snake! My length is " << length << ". Am I venomous? " << isVenomous << std::endl;
}

Animal* Snake::clone() const 
{
	return new Snake(*this);
}

size_t Snake::getSnakeLength() const
{
    	return length;
}
bool Snake::getIsVenomous() const
{
    	return isVenomous;
}

SnakeCreator::SnakeCreator() : AnimalCreator("snake")
{}

Animal* SnakeCreator::createAnimal(std::istream& is) const
{
    	size_t length;
    	bool isVenomous;
    	is >> length >> isVenomous;
    	return new Snake(length, isVenomous);
}

static SnakeCreator __;
