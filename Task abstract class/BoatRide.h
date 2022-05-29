#pragma once

#include "StageOfTrip.h"

class BoatRide : public StageOfTrip
{
public:

	BoatRide(double pricePerKM = 1.0, double distanceKM = 10.0);

	void setPricePerKM(double);
	void setDistanceKM(double);

	double getPricePerKM() const;
	double getDistanceKM() const;

	virtual double price() const override;

private:
	double pricePerKM;
	double distanceKM;
};