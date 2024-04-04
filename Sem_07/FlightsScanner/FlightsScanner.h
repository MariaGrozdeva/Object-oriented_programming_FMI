#pragma once
#include <fstream>

class FlightsScanner
{
public:
	FlightsScanner(const char* inputFileName, const char* outputFileName);
	void run();
	
private:
	struct FlightRecord
	{
	    	static constexpr size_t airportCodeSize = 3;
		char origin[airportCodeSize + 1];
		char dest[airportCodeSize + 1];
		unsigned int amount;
	};

    	static constexpr size_t maxFileNameSize = 32;
	char inputFileName[maxFileNameSize + 1] = "";
	char outputFileName[maxFileNameSize + 1] = "";

	void handleAirportCode(char* airportCode) const;
	void parseLine(const char* line, FlightRecord& record) const;

	void saveRecord(std::ofstream& ofs, const FlightRecord& record) const;
	bool readAndExportData(std::ifstream& ifs) const;
};
