#include "VehicleFactory.h"
#include "Car.h"
#include "Bike.h"
#include "Truck.h"

Vehicle* VehicleFactory::create(const std::string& type)
{
	if (type == "car") return new Car();
	if (type == "bike") return new Bike();
	if (type == "truck") return new Truck();
	return nullptr;
}
