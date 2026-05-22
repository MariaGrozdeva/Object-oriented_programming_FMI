#pragma once
#include "Vehicle.h"

class Car : public Vehicle
{
public:
	void describe() const override;
};
