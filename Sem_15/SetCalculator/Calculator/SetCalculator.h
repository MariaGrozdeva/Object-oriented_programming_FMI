#pragma once
#include "SetExpression.h"
#include "Singleton.h"
#include "Operation.h"
#include <string>

class SetCalculator
{
private:
	SetExpression* ptr;

	void copyFrom(const SetCalculator& other);
	void free();

	SetExpression* parse(const std::string& str);
	bool isOperation(char ch) const;

public:
	SetCalculator(const SetCalculator& other);
	SetCalculator& operator=(const SetCalculator& other);
	~SetCalculator();

	SetCalculator(const std::string& str);

	bool isElementIn(const SetExpression::Element& el) const;
};