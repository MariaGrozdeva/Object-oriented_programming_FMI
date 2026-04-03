#include "FlightsScanner.h"

int main()
{
	FlightsScanner scanner("inputFlights.txt", "outputFlights.txt");
	scanner.run();
}