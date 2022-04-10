
#include "ComputerPartWriter.h"


//PUBLIC----------------------------------------------------------------------------


ComputerPartWriter::ComputerPartWriter(const char* fileName) {
	openFile(fileName);
}

ComputerPartWriter::ComputerPartWriter(const ComputerPartWriter& other) {
	openFile(other.fileName);
}

ComputerPartWriter& ComputerPartWriter::operator=(const ComputerPartWriter& other) {
	if (this != &other) {
		openFile(other.fileName);
	}

	return *this;
}

ComputerPartWriter::~ComputerPartWriter() {
	closeFile();
	delete[] fileName;
}


bool ComputerPartWriter::openFile(const char* fileName) {
	if (!copyFileName(fileName))
		return false;

	closeFile();

	return openFile();
}

bool ComputerPartWriter::openFile() {
	if (ofile.is_open())
		return true;

	ofile.open(fileName, std::ios::app);
	if (!ofile.is_open()) {
		ofile.clear();
		return false;
	}

	return true;
}
void ComputerPartWriter::closeFile() {
	if (ofile.is_open())
		ofile.close();

	ofile.clear();
}


// Returns -1 if file is not opened,
//			0 if there was an error during writing to the file (possible corruption of the file),
//			1 if operation was successful,
//			2 if 'CP' is uninitialized object (does not write it in file).
int ComputerPartWriter::writeCPInFile(const ComputerPart& CP) {	
	if (!ofile.is_open())
		return -1;

	if (CP.isObjInit()) {
		ofile << '{' << CP.getType() << '|' << CP.getBrand()
			<< '|' << CP.getModel() << '|' << CP.getWarranty()
			<< '|' << CP.getPrice() << "}\n";
	}
	else {
		return 2;
	}

	if (ofile.good()) {
		// ??? I don't know if i shoul flush after every writing of an object ???
		// I don't think it is efficient to flush every time
		// but it is necessary if you want to read from the file right after.
		ofile.flush();	
		return 1;
	}
		
	ofile.clear();
	return 0;
}


const char* ComputerPartWriter::getFileName() { return fileName; }
bool ComputerPartWriter::isOpen() { return ofile.is_open(); }

//PRIVATE----------------------------------------------------------------------------

bool ComputerPartWriter::copyFileName(const char* newFileName) {
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
