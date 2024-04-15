#pragma once
#include <iostream>

class ComplexNumber
{
private:
	double real = 0;
	double im = 0;

public:
	ComplexNumber(double real, double im);

	ComplexNumber getComplexConjugate() const;
	
	void setReal(double real);
	void setIm(double im);

	double getReal() const;
	double getIm() const;

	ComplexNumber& operator+=(const ComplexNumber&);
	ComplexNumber& operator-=(const ComplexNumber&);
	ComplexNumber& operator*=(const ComplexNumber&);
	ComplexNumber& operator/=(const ComplexNumber&);

	// These should be friend functions because they are binary functions and their first arguments are NOT objects of our class ComplexNumber.
	friend std::ostream& operator<<(std::ostream&, const ComplexNumber&);
	friend std::istream& operator>>(std::istream&, ComplexNumber&);
};

ComplexNumber operator+(const ComplexNumber&, const ComplexNumber&);
ComplexNumber operator-(const ComplexNumber&, const ComplexNumber&);
ComplexNumber operator*(const ComplexNumber&, const ComplexNumber&);
ComplexNumber operator/(const ComplexNumber&, const ComplexNumber&);

bool operator==(const ComplexNumber&, const ComplexNumber&);
bool operator!=(const ComplexNumber&, const ComplexNumber&);
