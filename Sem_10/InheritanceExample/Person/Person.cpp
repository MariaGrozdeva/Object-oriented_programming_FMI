#include "Person.h"

Person::Person()
{
    this->name = new (std::nothrow) char[strlen("name") + 1];
    if (name != nullptr)
    {
        strcpy(this->name, "name");
        age = 0;
    }
}

Person::Person(const char* name, unsigned age):name(nullptr), age(0)
{
    try
    {
        setName(name);
        setAge(age);
    }
    catch (const std::bad_alloc& err)
    {
        free();
        throw;
    }
    catch (const std::invalid_argument& err)
    {
        free();
        throw;
    }
}

Person::Person(const Person& other) :name(nullptr), age(0)
{
    try
    {
        setName(other.name);
        setAge(other.age);
    }
    catch (const std::bad_alloc& err)
    {
        free();
        throw;
    }
}

Person::Person(Person&& other) noexcept
{
    moveFrom(std::move(other));
}

Person& Person::operator=(const Person& other)
{
    if (this == &other)
    {
        return *this;
    }

    char* tempName = new(std::nothrow) char[strlen(other.name) + 1];
    if (tempName == nullptr)
    {
        return *this;
    }
    strcpy(tempName, other.name);
    free();
    
    this->name = tempName;
    this->age = other.age;
    
    return *this;
}

Person& Person::operator=(Person&& other) noexcept
{
    if (this == &other)
    {
        return*this;
    }
    free();
    moveFrom(std::move(other));

    return *this;
}

Person::~Person()
{
    free();
}

void Person::setName(const char* name)
{
    if (name == nullptr || this->name == name)
    {
        throw std::invalid_argument("Invalid name!");
    }
    char* tempName = new char[strlen(name) + 1];
    strcpy(tempName, name);
    delete[] this->name;
    this->name = tempName;
}

void Person::setAge(unsigned age)
{
    if (age > 116)
    {
        throw std::invalid_argument("Invalid age!");
    }
    this->age = age;
}

const char* Person::getName() const
{
    return name;
}

unsigned Person::getAge() const
{
    return age;
}

void Person::print() const
{
    std::cout << name << " " << age << std::endl;
}

void Person::free()
{
    delete[] name;
    name = nullptr;
    age = 0;
}

void Person::moveFrom(Person&& other)
{
    this->name = other.name;
    this->age = other.age;

    other.name = nullptr;
    other.age = 0;
}
