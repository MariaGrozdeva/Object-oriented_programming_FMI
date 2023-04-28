#pragma once
#include <fstream>

class FlightsScanner
{
private:
	struct FlightRecord
	{
		char origin[64];
		char dest[64];
		unsigned int amount;
	};

	char inputFileName[1024] = "";
	char outputFileName[1024] = "";

	void handleAirportCode(char* airportCode) const;
	void parseLine(const char* line, FlightRecord& record) const;

	void saveRecord(std::ofstream& ofs, const FlightRecord& record) const;
	bool readAndExportData(std::ifstream& ifs) const;

public:
	FlightsScanner(const char* input, const char* output);
	void run();
};