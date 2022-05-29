
#include "BoatRide.h"

BoatRide::BoatRide(double pricePerKM, double distanceKM) {
	setPricePerKM(pricePerKM);
	setDistanceKM(distanceKM);
}

void BoatRide::setPricePerKM(double newPrice) {
	if (newPrice < 0.0)
		throw "Invalid price!";
	
	pricePerKM = newPrice;
}
void BoatRide::setDistanceKM(double newDistance) {
	if (newDistance <= 0.0)
		throw "Invalid distance!";

	distanceKM = newDistance;
}

double BoatRide::getPricePerKM() const { return pricePerKM; }
double BoatRide::getDistanceKM() const { return distanceKM; }

double BoatRide::price() const {
	return pricePerKM * distanceKM;
}