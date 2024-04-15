#include "GpsPath.h"
#include <iostream>

int main()
{
	GPSPath p;

	p.addPoint(1, 2);
	p.addPoint(1, 4);
	p.addPoint(1, 10);
	p.changePoint(1, 12, 1);

	std::cout << p.getDistance();
}