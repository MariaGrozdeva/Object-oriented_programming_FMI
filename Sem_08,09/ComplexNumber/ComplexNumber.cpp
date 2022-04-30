#include "ComplexNumber.h"

ComplexNumber::ComplexNumber() : ComplexNumber(0, 0)
{}
ComplexNumber::ComplexNumber(double real, double im)
{
	this->real = real;
	this->im = im;
}

ComplexNumber ComplexNumber::getComplexConjugate() const
{
	ComplexNumber complexConjugate(*this);
	complexConjugate.im *= (-1);

	return complexConjugate;
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
	return lhs - rhs == 0;
}

std::ostream& operator<<(std::ostream& os, const ComplexNumber& cN)
{
	return os << cN.real << " + i" << cN.im;
}
std::istream& operator>>(std::istream& is, ComplexNumber& cN)
{
	return is >> cN.real >> cN.im;
}