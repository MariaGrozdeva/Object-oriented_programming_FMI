#include "Farm.h"

int main()
{
	Farm myFarm;

	while (true)
	{
		size_t animalId;
		std::cin >> animalId;

		bool result = myFarm.addAnimal((Animal::AnimalType)animalId);

		if (result)
		{
			system("cls");

			std::cout << "Current number of animals in the farm: " << myFarm.getCount() << std::endl << std::endl;

			std::cout << "They say hello:" << std::endl;
			for (size_t i = 0; i < myFarm.getCount(); i++)
				myFarm[i]->sayHello();
		}
		else
			std::cout << "Invalid animal type!" << std::endl;
	}
}