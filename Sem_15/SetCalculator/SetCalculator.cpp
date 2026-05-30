#include "SetCalculator.h"
#include <cstdint>

// -------------------- Singleton --------------------

SetCalculator::Singleton::Singleton(char name) : name(name)
{}

bool SetCalculator::Singleton::isElementIn(const Element& el) const
{
	return el.get(name);
}

void SetCalculator::Singleton::markUsedVariables(uint32_t& used) const
{
	used |= (1u << (name - 'A'));
}

SetCalculator::SetExpression* SetCalculator::Singleton::clone() const
{
	return new Singleton(*this);
}

// -------------------- UnaryOperation --------------------

SetCalculator::UnaryOperation::UnaryOperation(char op, SetExpression* sub) : op(op), sub(sub)
{}

bool SetCalculator::UnaryOperation::isElementIn(const Element& el) const
{
	switch (op)
	{
	case '!': return !sub->isElementIn(el);
	}
	return false;
}

void SetCalculator::UnaryOperation::markUsedVariables(uint32_t& used) const
{
	sub->markUsedVariables(used);
}

SetCalculator::SetExpression* SetCalculator::UnaryOperation::clone() const
{
	return new UnaryOperation(op, sub->clone());
}

SetCalculator::UnaryOperation::~UnaryOperation()
{
	delete sub;
}

// -------------------- BinaryOperation --------------------

SetCalculator::BinaryOperation::BinaryOperation(char op, SetExpression* left, SetExpression* right) : op(op), left(left), right(right)
{}

bool SetCalculator::BinaryOperation::isElementIn(const Element& el) const
{
	switch (op)
	{
	case 'v': return left->isElementIn(el) || right->isElementIn(el);
	case '^': return left->isElementIn(el) && right->isElementIn(el);
	case '\\': return left->isElementIn(el) && !right->isElementIn(el);
	case 'x': return (left->isElementIn(el) && !right->isElementIn(el)) || (!left->isElementIn(el) && right->isElementIn(el));
	}
	return false;
}

void SetCalculator::BinaryOperation::markUsedVariables(uint32_t& used) const
{
	left->markUsedVariables(used);
	right->markUsedVariables(used);
}

SetCalculator::SetExpression* SetCalculator::BinaryOperation::clone() const
{
	return new BinaryOperation(op, left->clone(), right->clone());
}

SetCalculator::BinaryOperation::~BinaryOperation()
{
	delete left;
	delete right;
}

// -------------------- SetCalculator --------------------

bool SetCalculator::isOperation(char ch) const
{
	return ch == 'v' || ch == '^' || ch == '\\' || ch == 'x' || ch == '!';
}

SetCalculator::SetExpression* SetCalculator::parse(const std::string& str)
{
	if (str.size() == 1)
	{
		return new Singleton(str[0]);
	}

	std::string withoutBrackets = str.substr(1, str.size() - 2);

	size_t count = 0;
	for (size_t i = 0; i < withoutBrackets.size(); i++)
	{
		if (withoutBrackets[i] == '(')
		{
			count++;
		}
		else if (withoutBrackets[i] == ')')
		{
			count--;
		}
		else if (count == 0 && isOperation(withoutBrackets[i]))
		{
			if (withoutBrackets[i] == '!')
			{
				return new UnaryOperation('!', parse(withoutBrackets.substr(i + 1)));
			}
			else
			{
				return new BinaryOperation(withoutBrackets[i], parse(withoutBrackets.substr(0, i)), parse(withoutBrackets.substr(i + 1)));
			}
		}
	}
	return nullptr;
}

SetCalculator::Element SetCalculator::createFromMask(uint32_t mask, uint32_t used)
{
	Element el;
	for (int i = 0; i < 26; i++)
	{
		if (used & (1u << i))
		{
			el.set('A' + i, mask & 1);
			mask >>= 1;
		}
	}
	return el;
}

bool SetCalculator::checkAllAssignments(const SetExpression* lhs, const SetExpression* rhs)
{
	uint32_t used = 0;
	lhs->markUsedVariables(used);
	rhs->markUsedVariables(used);

	size_t varCount = 0;
	for (int i = 0; i < 26; i++)
	{
		if (used & (1u << i))
		{
			varCount++;
		}
	}

	size_t assignmentsCount = (1u << varCount);
	for (size_t mask = 0; mask < assignmentsCount; mask++)
	{
		Element el = createFromMask(mask, used);
		if (lhs->isElementIn(el) != rhs->isElementIn(el))
		{
			return false;
		}
	}
	return true;
}

void SetCalculator::copyFrom(const SetCalculator& other)
{
	ptr = other.ptr->clone();
}

void SetCalculator::free()
{
	delete ptr;
}

SetCalculator::SetCalculator(const std::string& str)
{
	ptr = parse(str);
}

SetCalculator::SetCalculator(const SetCalculator& other)
{
	copyFrom(other);
}

SetCalculator& SetCalculator::operator=(const SetCalculator& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

SetCalculator::~SetCalculator()
{
	free();
}

bool SetCalculator::isElementIn(const Element& el) const
{
	return ptr->isElementIn(el);
}

bool SetCalculator::isSameSet(const SetCalculator& other) const
{
	return checkAllAssignments(ptr, other.ptr);
}
