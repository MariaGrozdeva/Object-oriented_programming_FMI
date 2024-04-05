#include "FlightsScanner.h"
#include "Utils.h"
#include <iostream>
#include <cstring>
#include <sstream>

#pragma warning (disable : 4996)

FlightsScanner::FlightsScanner(const char* inputFileName, const char* outputFileName)
{
	strcpy(this->inputFileName, inputFileName);
	strcpy(this->outputFileName, outputFileName);
}

void FlightsScanner::run()
{
	std::ifstream ifs(inputFileName);
	if (!ifs.is_open())
	{
		std::cout << "File not found!" << std::endl;
		return;
	}

	if (readAndExportData(ifs))
	{
		std::cout << "Successfully exported file!" << std::endl;
	}
	else
	{
		std::cout << "Error occurred while exporting the file!" << std::endl;
	}
	ifs.close();
}

void FlightsScanner::handleAirportCode(char* airportCode) const
{
	if (strlen(airportCode) != FlightRecord::airportCodeSize)
	{
		throw std::length_error("The airport code size should be exactly 3");
	}
	toUpper(airportCode);
}

void FlightsScanner::parseLine(const char* line, FlightsScanner::FlightRecord& record) const
{
	std::stringstream current(line);

	current >> record.origin;
	try
	{
		handleAirportCode(record.origin);
	}
	catch (const std::length_error& e)
	{
		std::cout << "Error while processing the origin. Given: " << record.origin << std::endl;
		throw;
	}

	current >> record.dest;
	try
	{
		handleAirportCode(record.dest);
	}
	catch (const std::length_error& e)
	{
		std::cout << "Error while processing the destination. Given: " << record.dest << std::endl;
		throw;
	}

	char amountStr[6];
	current >> amountStr;
	try
	{
		record.amount = strToNumber(amountStr);
	}
	catch (const std::bad_cast& e)
	{
		static constexpr unsigned int DEFAULT_AMOUNT = 50;
		std::cout << "Invalid amount. Setting to default value: " << DEFAULT_AMOUNT << std::endl;
		record.amount = DEFAULT_AMOUNT;
		throw;
	}
}

void FlightsScanner::saveRecord(std::ofstream& ofs, const FlightRecord& record) const
{
	const float euroToLev = 1.95;
	ofs << record.origin << " " << record.dest << " " << record.amount * euroToLev << std::endl;
}

bool FlightsScanner::readAndExportData(std::ifstream& ifs) const
{
	std::ofstream ofs(outputFileName, std::ios::trunc);
	if (!ofs.is_open())
	{
		std::cout << "File could not be open." << std::endl;
		return false;
	}

	unsigned int lineIndex = 0;

	bool errorOccurred = false;
	while (!ifs.eof())
	{
		char line[1024];
		ifs.getline(line, 1024);

		FlightRecord record;
		try
		{
			parseLine(line, record);
			saveRecord(ofs, record);
		}
		catch (const std::length_error& e)
		{
			std::cout << "The length error \"" << e.what() << "\" occurred on line " << lineIndex << ". The flight will NOT be saved!" << std::endl;
			errorOccurred = true;
		}
		catch (const std::bad_cast& e)
		{
			std::cout << "The bad cast error \"" << e.what() << "\" occurred on line " << lineIndex << ". The flight will be saved!" << std::endl;
			saveRecord(ofs, record);
			errorOccurred = true;
		}
		catch (const std::exception& e)
		{
			std::cout << "The unknown error \"" << e.what() << "\" ccured on line " << lineIndex << ". The flight will NOT be saved!" << std::endl;
			errorOccurred = true;
		}
		lineIndex++;
	}
	return errorOccurred;
}
