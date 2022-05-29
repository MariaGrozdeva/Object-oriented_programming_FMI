#pragma once

#include "StageOfTrip.h"

class PlaneRide : public StageOfTrip
{
public:

	PlaneRide(double ticketPrice, const char* code);

	virtual double price() const override;
	const char* getCode() const;

	void setTicketPrice(double);
	void setCode(const char*);

private:

	bool isLet(char c) const;
	bool isNum(char c) const;

private:
	double ticketPrice;
	char code[7];
};

