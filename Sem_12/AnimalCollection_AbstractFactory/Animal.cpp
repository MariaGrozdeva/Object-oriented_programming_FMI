#include "Animal.h"
#include "AnimalFactory.hpp"

AnimalCreator::AnimalCreator(const std::string& animalName) : animalName(animalName)
{
        AnimalFactory::getFactory().registerAnimalCreator(this);
}

const char* AnimalCreator::getAnimalName() const
{
        return animalName;
}
