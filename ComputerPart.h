
#pragma once
#include <iostream>
#include <cstring>
#pragma warning (disable:4996)


const char PART_TYPE_NAMES[][11]{ "MONITOR", "COMPUTER", "LAPTOP", "MOUSE", "KEYBOARD", "HEADPHONES", "CAMERA" };

class ComputerPart {
private:
	enum PartType {
		UNDEF = -1,

		MONITOR,
		COMPUTER,
		LAPTOP,
		MOUSE,
		KEYBOARD,
		HEADPHONES,
		CAMERA,

		END
	};

private:
	char* brand;
	char* model;
	double price;
	size_t warranty;
	PartType type;
	bool IS_OBJ_INIT{false};		// True if the object was initialised by the user. User can change the object only once (except for 'price').

public:

	ComputerPart();
	ComputerPart(const char* brand, const char* model, double price, size_t warranty, const char* partType);
	ComputerPart(const ComputerPart&);
	~ComputerPart();
	ComputerPart& operator=(const ComputerPart&) = delete;	// Use 'setComputerPartOnce()' instead.

	bool setPrice(double price);			// True if OK

	int setComputerPartOnce(const char* brand, const char* model, double price, size_t warranty, const char* partType);
	int setComputerPartOnce(const ComputerPart&);

	const char* getBrand() const;
	const char* getModel() const;
	double getPrice() const;
	size_t getWarranty() const;
	const char* getType() const;
	bool isObjInit() const;

	void print() const;

private:

	bool setWarranty(size_t);				// True if OK.
	bool setType(const char* partType);		// True if OK.
	void Null();							// Set object in uninitialized state
};