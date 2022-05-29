#pragma once

class StageOfTrip
{
public:
	virtual double price() const = 0;
	virtual ~StageOfTrip() {}
};