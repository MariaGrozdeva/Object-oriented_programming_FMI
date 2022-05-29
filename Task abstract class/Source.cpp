
#include <iostream>
#include "BoatRide.h"
#include "PlaneRide.h"


double calculatePrice(StageOfTrip** steps, size_t stepCount, size_t people) {
	double price = 0;
	for (size_t i = 0; i < stepCount; ++i)
		price += steps[i]->price();

	return price * people;
}

int main()
{
	StageOfTrip** steps = new StageOfTrip*[4];
	steps[0] = new BoatRide{ 1.0, 5.0};
	steps[1] = new PlaneRide{ 10.0, "MK1234" };
	steps[2] = new PlaneRide{ 15.0, "MK5555" };
	steps[3] = new BoatRide{ 1.0, 20.0};

	std::cout << calculatePrice(steps, 4, 3);
}