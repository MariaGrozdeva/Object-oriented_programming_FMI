#pragma once
#include "Animal.h"
#include <cassert>
#include <cstring>
#include <limits>
#include <string>

class AnimalFactory
{
public:
    static AnimalFactory& getFactory()
    {
        static AnimalFactory factory;
        return factory;
    }

    void registerAnimalCreator(const AnimalCreator* creator)
    {
        assert(count < MAX_CREATORS_COUNT);
        creators[count++] = creator;
    }

    Animal* createAnimal(std::istream& is)
    {
        char name[32];
        is >> name;

        const AnimalCreator* creator = getCreator(name);
        if (creator)
        {
            return creator->createAnimal(is);
        }
        else 
        {
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return nullptr;
        }
    }
    
private:
    static constexpr size_t MAX_CREATORS_COUNT = 10;
    const AnimalCreator* creators[MAX_CREATORS_COUNT];
    size_t count;
    
    const AnimalCreator* getCreator(const char* str) const
    {
        for (size_t i = 0; i < count; i++)
        {
            if (strcmp(creators[i]->getAnimalName(), str) == 0)
            {
                return creators[i];
            }
        }
        return nullptr;
    }
    
    AnimalFactory() : count(0)
    {};
    ~AnimalFactory() = default;
    AnimalFactory(const AnimalFactory&) = delete;
    AnimalFactory& operator=(const AnimalFactory&) = delete;
};