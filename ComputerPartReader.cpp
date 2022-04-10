
#include "ComputerPartReader.h"

//PUBLIC----------------------------------------------------------------------------

ComputerPartReader::ComputerPartReader(const char* newFileName) {
	openFile(newFileName);
}

ComputerPartReader::ComputerPartReader(const ComputerPartReader& other) {
	openFile(other.fileName);
}

ComputerPartReader& ComputerPartReader::operator=(const ComputerPartReader& other) {
	if (this != &other) {
		openFile(other.fileName);
	}

	return *this;
}

ComputerPartReader::~ComputerPartReader() {
	closeFile();
	delete[] fileName;
}


bool ComputerPartReader::openFile(const char* newFileName) {
	if (!copyFileName(newFileName))
		return false;

	closeFile();

	return openFile();
}
bool ComputerPartReader::openFile(){ 
	if (ifile.is_open())
		return true;

	ifile.open(fileName, std::ios::app);
	if (!ifile.is_open()) {
		ifile.clear();
		return false;
	}

	return true;
}
void ComputerPartReader::closeFile() {
	if (ifile.is_open())
		ifile.close();

	ifile.clear();
}

// Returns -1 if file is not opened,
//			0 if an error occurs during reading, or is incorectly formatted (nothing is written in the object),
//			1 if operation was successful,
int ComputerPartReader::readCPFromFile(ComputerPart& CP) {
	if (!ifile.is_open())
		return -1;

	char c = 0;
	ifile >> c;
	if (c != '{') {
		ifile.clear();
		return 0;
	}
		
	char type[MAX_SIZE];
	ifile.getline(type, MAX_SIZE, '|');
	
	char brand[MAX_SIZE];
	ifile.getline(brand, MAX_SIZE, '|');

	char model[MAX_SIZE];
	ifile.getline(model, MAX_SIZE, '|');

	size_t warranty = 0;
	ifile >> warranty;
	
	ifile >> c;
	if (c != '|') {
		ifile.clear();
		return 0;
	}
		
	double price = -1.0;
	ifile >> price;

	ifile >> c;
	if (c != '}' || !ifile.good()) {
		ifile.clear();
		return 0;
	}

	// If the file formating is correct but
	// the computer part info is invalid, count it as an error.
	if (1 != CP.setComputerPartOnce(brand, model, price, warranty, type)) {
		return 0;
	}

	return 1;
}

const char* ComputerPartReader::getFileName() { return fileName; }
bool ComputerPartReader::isOpen() { return ifile.is_open(); }


//PRIVATE----------------------------------------------------------------------------


bool ComputerPartReader::copyFileName(const char* newFileName) {
	if (!newFileName)
		return false;

	size_t len = strlen(newFileName);
	if (len == 0)		// Don't accept empty names.
		return false;

	delete[] fileName;
	fileName = new char[len + 1];
	strcpy(fileName, newFileName);

	return true;
}