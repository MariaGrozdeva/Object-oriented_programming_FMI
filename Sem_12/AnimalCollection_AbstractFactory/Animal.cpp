#include "Animal.h"
#include "AnimalFactory.hpp"

AnimalCreator::AnimalCreator(const char* animalName) : animalName(animalName)
{
        AnimalFactory::getFactory().registerAnimalCreator(this);
}

const char* AnimalCreator::getAnimalName() const
{
        return animalName.c_str();
}
