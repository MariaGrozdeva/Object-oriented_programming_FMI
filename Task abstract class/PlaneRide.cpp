#include "PlaneRide.h"


PlaneRide::PlaneRide(double ticketPrice, const char* code) {
	setCode(code);
	setTicketPrice(ticketPrice);
}

double PlaneRide::price() const { return ticketPrice; }
const char* PlaneRide::getCode() const { return code; }

void PlaneRide::setTicketPrice(double newPrice) {
	if (newPrice < 0.0)
		throw "Invalid ticket price!";
	ticketPrice = newPrice;
}
void PlaneRide::setCode(const char* code) {
	if (!code)
		throw "Dereferencing nullptr!";
	
	if (isLet(code[0]) && isLet(code[1]) && isNum(code[2]) &&
		isNum(code[3]) && isNum(code[4]) && isNum(code[5]))
	{
		for (size_t i = 0; i < 6; ++i)
			this->code[i] = code[i];
		
		this->code[6] = '\0';
		return;
	}
	
	throw "Invalid code!";
}

bool PlaneRide::isLet(char c) const { return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'); }

bool PlaneRide::isNum(char c) const { return '0' <= c && c <= '9'; }