#include "FlightsScanner.h"
#include "Exceptions.h"
#include "Utils.h"
#include <iostream>
#include <cstring>
#include <sstream>

#pragma warning(disable : 4996)

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
        std::cout << "Errors occurred while exporting the file!" << std::endl;
    }

    ifs.close();
}

void FlightsScanner::parseLine(const char* line, FlightsScanner::FlightRecord& record) const
{
    std::stringstream current(line);
    char temp[1024];

    // Parse origin
    current >> temp;
    if (strlen(temp) != FlightRecord::airportCodeSize)
    {
        throw std::length_error("Invalid origin '" + std::string(temp) + "': Airport code must be exactly 3 characters");
    }
    strcpy(record.origin, temp);
    toUpper(record.origin);

    // Parse destination
    current >> temp;
    if (strlen(temp) != FlightRecord::airportCodeSize)
    {
        throw std::length_error("Invalid destination '" + std::string(temp) + "': Airport code must be exactly 3 characters");
    }
    strcpy(record.dest, temp);
    toUpper(record.dest);

    // Parse price
    current >> temp;
    try
    {
        record.price = strToNumber(temp);
    }
    catch (const NonDigitCharException& e)
    {
        static constexpr unsigned int DEFAULT_PRICE = 50;
        std::cout << "  [Line warning] Invalid price '" << temp
                  << "' (bad character: '" << e.getChar()
                  << "'). Using default: " << DEFAULT_PRICE << std::endl;
        record.price = DEFAULT_PRICE;
    }
}

void FlightsScanner::saveRecord(std::ofstream& ofs, const FlightRecord& record) const
{
    constexpr double euroToLev = 1.95;
    ofs << record.origin << " " << record.dest << " " << record.price * euroToLev << std::endl;
}

bool FlightsScanner::readAndExportData(std::ifstream& ifs) const
{
    std::ofstream ofs(outputFileName, std::ios::trunc);
    if (!ofs.is_open())
    {
        std::cout << "Could not open output file." << std::endl;
        return false;
    }

    unsigned int lineIndex = 1;
    bool errorOccurred = false;

    char line[1024];
    while (ifs.getline(line, 1024))
    {
        if (strlen(line) == 0)
        {
            lineIndex++;
            continue;
        }

        std::cout << "[Line " << lineIndex << "] Processing: \"" << line << "\"" << std::endl;

        FlightRecord record;
        try
        {
            parseLine(line, record);
            saveRecord(ofs, record);
            std::cout << "[Line " << lineIndex << "] Saved successfully: "
                      << record.origin << " -> " << record.dest
                      << " | Price: " << record.price << " EUR ("
                      << record.price * 1.95 << " BGN)" << std::endl;
        }
        catch (const std::length_error& e)
        {
            std::cout << "[Line " << lineIndex << "] Skipped: " << e.what() << std::endl;
            errorOccurred = true;
        }
        catch (const NonLetterCharException& e)
        {
            std::cout << "[Line " << lineIndex << "] Skipped: invalid character '"
                      << e.getChar() << "' in airport code" << std::endl;
            errorOccurred = true;
        }
        catch (const NullStringException&)
        {
            std::cout << "[Line " << lineIndex << "] Skipped: null string encountered" << std::endl;
            errorOccurred = true;
        }

        lineIndex++;
    }

    return !errorOccurred;
}
