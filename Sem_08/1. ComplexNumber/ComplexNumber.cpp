#include "ComplexNumber.h"

ComplexNumber::ComplexNumber(double real, double im)
{
	this->real = real;
	this->im = im;
}

ComplexNumber ComplexNumber::getComplexConjugate() const
{
	ComplexNumber complexConjugate(real, (-1)*im);
	return complexConjugate;
}

void ComplexNumber::setReal(double real)
{
    	this->real = real;
}
void ComplexNumber::setIm(double im)
{
    	this->im = im;
}

double ComplexNumber::getReal() const
{
	return real;
}
double ComplexNumber::getIm() const
{
	return im;
}

ComplexNumber& ComplexNumber::operator+=(const ComplexNumber& other)
{
	real += other.real;
	im += other.im;
	return *this;
}
ComplexNumber& ComplexNumber::operator-=(const ComplexNumber& other)
{
	real -= other.real;
	im -= other.im;
	return *this;
}
ComplexNumber& ComplexNumber::operator*=(const ComplexNumber& other)
{
	double originalReal = real;
	real = real * other.real - im * other.im;
	im = originalReal * other.im + im * other.real;
	return *this;
}
ComplexNumber& ComplexNumber::operator/=(const ComplexNumber& other)
{
	ComplexNumber complexConjugate = other.getComplexConjugate();
	ComplexNumber otherCopy(other);

	*this *= complexConjugate;
	otherCopy *= complexConjugate;

	if (otherCopy.real) // To avoid division by zero.
	{
		real /= otherCopy.real;
		im /= otherCopy.real;
	}

	return *this;	
}

ComplexNumber operator+(const ComplexNumber& lhs, const ComplexNumber& rhs)
{
	ComplexNumber result(lhs);
	result += rhs;
	return result;
}
ComplexNumber operator-(const ComplexNumber& lhs, const ComplexNumber& rhs)
{
	ComplexNumber result(lhs);
	result -= rhs;
	return result;
}
ComplexNumber operator*(const ComplexNumber& lhs, const ComplexNumber& rhs)
{
	ComplexNumber result(lhs);
	result *= rhs;
	return result;
}
ComplexNumber operator/(const ComplexNumber& lhs, const ComplexNumber& rhs)
{
	ComplexNumber result(lhs);
	result /= rhs;
	return result;
}

bool operator==(const ComplexNumber& lhs, const ComplexNumber& rhs)
{
	return lhs.getReal() == rhs.getReal() && lhs.getIm() == rhs.getIm();
}
bool operator!=(const ComplexNumber& lhs, const ComplexNumber& rhs)
{
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const ComplexNumber& cN)
{
	return os << cN.real << " + i" << cN.im;
}
std::istream& operator>>(std::istream& is, ComplexNumber& cN)
{
	return is >> cN.real >> cN.im;
}
