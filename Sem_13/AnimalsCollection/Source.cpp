#include "Dog.h"
#include "Cat.h"
#include "Mouse.h"
#include "Farm.h"

int main()
{
	Farm f;
	f.addAnimal(Dog());
	f.addAnimal(Cat());

	f.allSayHello();
}