#include "AnimalCollection/Farm.h"

int main()
{
	Farm myFarm;

	while (true)
	{
		unsigned animalId;
		std::cin >> animalId;

		bool result = myFarm.addAnimal(static_cast<Animal::AnimalType>(animalId));

		if (result)
		{
			system("cls");

			std::cout << "Current number of animals in the farm: " << myFarm.size() << std::endl << std::endl;

			std::cout << "They say hello:" << std::endl;
			for (size_t i = 0; i < myFarm.size(); i++)
			{
				myFarm[i]->sayHello();
			}
		}
		else
		{
			std::cout << "Invalid animal type!" << std::endl;
		}
	}
}
