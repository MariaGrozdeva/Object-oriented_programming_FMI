#pragma once
#include "Vehicle.h"
#include <string>

class VehicleFactory
{
public:
	static Vehicle* create(const std::string& type);
};
