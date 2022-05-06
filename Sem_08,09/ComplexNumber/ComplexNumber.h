#pragma once

class ComplexNumber
{
private:
	double real;
	double im;

public:
	ComplexNumber(double real = 0, double im = 0);

	ComplexNumber getComplexConjugate() const;

	ComplexNumber& operator+=(const ComplexNumber&);
	ComplexNumber& operator-=(const ComplexNumber&);
	ComplexNumber& operator*=(const ComplexNumber&);
	ComplexNumber& operator/=(const ComplexNumber&);

	friend bool operator==(const ComplexNumber&, const ComplexNumber&);

	// These should be friend functions because they are binary functions and their first arguments are NOT objects of our class ComplexNumber.
	friend std::ostream& operator<<(std::ostream&, const ComplexNumber&);
	friend std::istream& operator>>(std::istream&, ComplexNumber&);
};

ComplexNumber operator+(const ComplexNumber&, const ComplexNumber&);
ComplexNumber operator-(const ComplexNumber&, const ComplexNumber&);
ComplexNumber operator*(const ComplexNumber&, const ComplexNumber&);
ComplexNumber operator/(const ComplexNumber&, const ComplexNumber&);
