
#pragma once
#include <fstream>
#include "ComputerPart.h"

class ComputerPartWriter {
private:
	std::ofstream ofile;
	char* fileName{ nullptr };

public:

	ComputerPartWriter(const char* fileName);
	ComputerPartWriter(const ComputerPartWriter&);
	ComputerPartWriter& operator=(const ComputerPartWriter&);
	~ComputerPartWriter();

	bool openFile(const char* fileName);		// Returns true if file was opened successfully. False if file can't be opened.
	bool openFile();							// Open file 'fileName'.
	void closeFile();							// Close file 'fileName'.
	
	int writeCPInFile(const ComputerPart&);		// Returns true if if was successful.

	const char* getFileName();
	bool isOpen();


private:

	bool copyFileName(const char* newFileName);	// Returns false if 'newFileName' is invalid file name.
};