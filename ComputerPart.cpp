
#include "ComputerPart.h"


//PUBLIC----------------------------------------------------------------------------

ComputerPart::ComputerPart() { Null(); }

ComputerPart::ComputerPart(const char* brand, const char* model, double price, size_t warranty, const char* partType) {
	Null();
	setComputerPartOnce(brand, model, price, warranty, partType);
}

ComputerPart::ComputerPart(const ComputerPart& other){
	Null();
	setComputerPartOnce(other);
}

ComputerPart::~ComputerPart(){
	delete[] brand;
	delete[] model;
}

bool ComputerPart::setPrice(double price) {
	if (price < 0.0) {
		return false;
	}

	this->price = price;
	return true;
}

// Returns -1 if parameters were invalid,
//			0 if object is already initialized,
//			1 if initialization was successful.
// If one of the function parameters is invalid, nothing is written in the object.
// The object is then set to uninitialized state.
int ComputerPart::setComputerPartOnce(const char* brand, const char* model, double price, size_t warranty, const char* partType) {
	if (IS_OBJ_INIT)
		return 0;
	
	// Check if the parameters are valid
	if (!setPrice(price) || !setType(partType) || !setWarranty(warranty) || !brand || !model) {
		Null();
		return -1;
	}

	size_t len = strlen(brand);
	if (len == 0 || strpbrk(brand, "{}|")) {	// Don't accept empty names. Names can not contain the simbols {}|
		Null();
		return -1;
	}
	this->brand = new char[len + 1];
	strcpy(this->brand, brand);

	len = strlen(model);
	if (len == 0 || strpbrk(model, "{}|")) {	// Don't accept empty names. Names can not contain the simbols {}|
		delete[] this->brand;
		Null();
		return -1;
	}
	this->model = new char[strlen(model) + 1];
	strcpy(this->model, model);

	IS_OBJ_INIT = true;
	return 1;
}

// Returns -1 if 'other' is uninitialized,
//			0 if object is already initialized,
//			1 if initialization was successful.
int ComputerPart::setComputerPartOnce(const ComputerPart& other){
	// No check for 'this != &other' 
	// because the followning 'ifs' will stop it.
	if (!other.IS_OBJ_INIT)
		return -1;
	
	if (IS_OBJ_INIT)
		return 0;

	price = other.price;
	type = other.type;
	warranty = other.warranty;

	brand = new char[strlen(other.brand) + 1];
	strcpy(brand, other.brand);
	model = new char[strlen(other.model) + 1];
	strcpy(model, other.model);

	IS_OBJ_INIT = true;
	return true;
}


const char* ComputerPart::getBrand() const { return brand; }
const char* ComputerPart::getModel() const { return model; }
double ComputerPart::getPrice()	const	   { return price; }
size_t ComputerPart::getWarranty() const   { return warranty; }
const char* ComputerPart::getType() const  { return PART_TYPE_NAMES[type]; }
bool ComputerPart::isObjInit() const	   { return IS_OBJ_INIT; }

void ComputerPart::print() const {
	if (IS_OBJ_INIT)
		std::cout << "\n{" << PART_TYPE_NAMES[type] << "|" << brand << "|" << model << "|" << warranty << "|" << price << "}";
	else
		std::cout << "\n{OBJECT 'ComputerPart' IS UNINITIALIZED}";
}

//PRIVATE----------------------------------------------------------------------------

bool ComputerPart::setWarranty(size_t warranty) {
	if (warranty > 100)
		return false;

	this->warranty = warranty;
	return true;
}

bool ComputerPart::setType(const char* partType) {

	//"MONITOR", "COMPUTER", "LAPTOP", "MOUSE", "KEYBOARD", "HEADPHONES", "CAMERA"
	int i = 0;
	for (; i < PartType::END; ++i) {
		if (strcmp(partType, PART_TYPE_NAMES[i]) == 0)
			break;
	}

	switch (i) {
	case MONITOR:	type = MONITOR;		break;
	case COMPUTER:	type = COMPUTER;	break;
	case LAPTOP:	type = LAPTOP;		break;
	case MOUSE:		type = MOUSE;		break;
	case KEYBOARD:	type = KEYBOARD;	break;
	case HEADPHONES:type = HEADPHONES;	break;
	case CAMERA:	type = CAMERA;		break;
	default:
		type = UNDEF;
		return false;
	}

	return true;
}

void ComputerPart::Null() {
	price = -1.0;
	warranty = 0;
	type = PartType::UNDEF;
	brand = nullptr;
	model = nullptr;
	IS_OBJ_INIT = false;
}