#include "VehicleFactory.h"

int main()
{
	const char* types[] = { "car", "bike", "truck", "boat" };

	for (const char* type : types)
	{
		Vehicle* v = VehicleFactory::create(type);
		if (v)
		{
			v->describe();
			delete v;
		}
		else
		{
			std::cout << "Unknown vehicle type: " << type << std::endl;
		}
	}
}
