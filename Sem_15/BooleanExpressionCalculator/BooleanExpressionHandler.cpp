#include "BooleanExpressionHandler.h"
#include <stdexcept>

namespace
{
	constexpr char NEG = '!';
	constexpr char AND = '&';
	constexpr char OR = '|';
	constexpr char IMPL = '>';
	constexpr char IFF = '=';
	constexpr char XOR = '+';

	constexpr size_t ALLOWED_CHARACTERS_COUNT = 26;
}

bool BooleanInterpretation::operator()(char ch) const
{
	if (!isValid(ch))
	{
		throw std::invalid_argument("Invalid character");
	}

	unsigned index = ch - 'a';
	return variables & (1 << index);
}

void BooleanInterpretation::set(char ch, bool value)
{
	if (!isValid(ch))
	{
		throw std::invalid_argument("Invalid character");
	}

	unsigned index = ch - 'a';
	if (value)
	{
		variables |= (1 << index);
	}
	else
	{
		variables &= ~(1 << index);
	}
}

bool BooleanInterpretation::isValid(char ch)
{
	return ch >= 'a' && ch <= 'z';
}

BooleanInterpretation BooleanInterpretation::createFromMask(uint32_t mask, uint32_t variables)
{
	BooleanInterpretation result{};
	for (size_t i = 0; i < ALLOWED_CHARACTERS_COUNT; i++)
	{
		if ((variables & (1 << i)) && (mask & 1))
		{
			result.set('a' + i, true);
			mask >>= 1;
		}
	}
	return result;
}

BooleanExpressionHandler::Variable::Variable(char ch)
{
	if (!BooleanInterpretation::isValid(ch))
	{
		throw std::invalid_argument("Invalid variable name");
	}

	this->ch = ch;
}

bool BooleanExpressionHandler::Variable::evaluate(const BooleanInterpretation& interpret) const
{
	return interpret(ch);
}

void BooleanExpressionHandler::Variable::markUsedCharacters(uint32_t& usedCharacters) const
{
	unsigned index = ch - 'a';
	usedCharacters |= (1 << index);
}

BooleanExpressionHandler::BooleanExpression* BooleanExpressionHandler::Variable::clone() const
{
	return new Variable(*this);
}

BooleanExpressionHandler::UnaryExpression::UnaryExpression(BooleanExpression* expression)
{
	this->expression = expression;
}

void BooleanExpressionHandler::UnaryExpression::markUsedCharacters(uint32_t& usedCharacters) const
{
	expression->markUsedCharacters(usedCharacters);
}

BooleanExpressionHandler::UnaryExpression::~UnaryExpression()
{
	delete expression;
	expression = nullptr;
}

BooleanExpressionHandler::Negation::Negation(BooleanExpression* expression) : UnaryExpression(expression)
{}

bool BooleanExpressionHandler::Negation::evaluate(const BooleanInterpretation& interpret) const
{
	return !expression->evaluate(interpret);
}

BooleanExpressionHandler::BooleanExpression* BooleanExpressionHandler::Negation::clone() const
{
	return new Negation(expression->clone());
}

BooleanExpressionHandler::BinaryExpression::BinaryExpression(BooleanExpression* lhs, BooleanExpression* rhs)
{
	this->lhs = lhs;
	this->rhs = rhs;
}

void BooleanExpressionHandler::BinaryExpression::markUsedCharacters(uint32_t& usedCharacters) const
{
	lhs->markUsedCharacters(usedCharacters);
	rhs->markUsedCharacters(usedCharacters);
}

BooleanExpressionHandler::BinaryExpression::~BinaryExpression()
{
	delete lhs, rhs;
	lhs = rhs = nullptr;
}

BooleanExpressionHandler::Conjunction::Conjunction(BooleanExpression* lhs, BooleanExpression* rhs) : BinaryExpression(lhs, rhs)
{}

bool BooleanExpressionHandler::Conjunction::evaluate(const BooleanInterpretation& interpret) const
{
	return lhs->evaluate(interpret) && rhs->evaluate(interpret);
}

BooleanExpressionHandler::BooleanExpression* BooleanExpressionHandler::Conjunction::clone() const
{
	return new Conjunction(lhs->clone(), rhs->clone());
}

BooleanExpressionHandler::Disjunction::Disjunction(BooleanExpression* lhs, BooleanExpression* rhs) : BinaryExpression(lhs, rhs)
{}

bool BooleanExpressionHandler::Disjunction::evaluate(const BooleanInterpretation& interpret) const
{
	return  lhs->evaluate(interpret) || rhs->evaluate(interpret);
}

BooleanExpressionHandler::BooleanExpression* BooleanExpressionHandler::Disjunction::clone() const
{
	return new Disjunction(lhs->clone(), rhs->clone());
}

BooleanExpressionHandler::Implication::Implication(BooleanExpression* lhs, BooleanExpression* rhs) : BinaryExpression(lhs, rhs)
{}

bool BooleanExpressionHandler::Implication::evaluate(const BooleanInterpretation& interpret) const
{
	return !lhs->evaluate(interpret) || rhs->evaluate(interpret);
}

BooleanExpressionHandler::BooleanExpression* BooleanExpressionHandler::Implication::clone() const
{
	return new Implication(lhs->clone(), rhs->clone());
}

BooleanExpressionHandler::BiImplication::BiImplication(BooleanExpression* lhs, BooleanExpression* rhs) : BinaryExpression(lhs, rhs)
{}

bool BooleanExpressionHandler::BiImplication::evaluate(const BooleanInterpretation& interpret) const
{
	return lhs->evaluate(interpret) == rhs->evaluate(interpret);
}

BooleanExpressionHandler::BooleanExpression* BooleanExpressionHandler::BiImplication::clone() const
{
	return new BiImplication(lhs->clone(), rhs->clone());
}

BooleanExpressionHandler::Xor::Xor(BooleanExpression* lhs, BooleanExpression* rhs) : BinaryExpression(lhs, rhs)
{}

bool BooleanExpressionHandler::Xor::evaluate(const BooleanInterpretation& interpret) const
{
	return lhs->evaluate(interpret) != rhs->evaluate(interpret);
}

BooleanExpressionHandler::BooleanExpression* BooleanExpressionHandler::Xor::clone() const
{
	return new Xor(lhs->clone(), rhs->clone());
}

bool BooleanExpressionHandler::checkAllTruthÀssignments(const BooleanExpression* expression, bool expected)
{
	uint32_t usedCharacters;
	expression->markUsedCharacters(usedCharacters);
 	size_t chCount = 0;
	for (size_t i = 0; i < ALLOWED_CHARACTERS_COUNT; i++)
	{
		if (usedCharacters & (1 << i))
		{
			chCount++;
		}
	}

	size_t truthÀssignmentsCount = (1 << chCount);
	for (size_t i = 0; i < truthÀssignmentsCount; i++)
	{
		if (expression->evaluate(BooleanInterpretation::createFromMask(i, usedCharacters)) != expected)
		{
			return false;
		}
	}
	return true;
}

BooleanExpressionHandler::BooleanExpression* BooleanExpressionHandler::factory(std::string_view str)
{
	str = str.substr(1, str.length() - 2); // remove the first and the last brackets

	if (str.length() == 1)
	{
		return new Variable(str[0]);
	}

	unsigned count = 0;
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] == '(')
		{
			count++;
		}
		else if (str[i] == ')')
		{
			count--;
		}
		else if (count == 0)
		{
			switch (str[i])
			{
			case NEG: return new Negation(factory(str.substr(i + 1, str.length() - i - 1)));
			case AND: return new Conjunction(factory(str.substr(0, i)), factory(str.substr(i + 1, str.length() - i - 1)));
			case OR: return new Disjunction(factory(str.substr(0, i)), factory(str.substr(i + 1, str.length() - i - 1)));
			case IMPL: return new Implication(factory(str.substr(0, i)), factory(str.substr(i + 1, str.length() - i - 1)));
			case IFF: return new BiImplication(factory(str.substr(0, i)), factory(str.substr(i + 1, str.length() - i - 1)));
			case XOR: return new Xor(factory(str.substr(0, i)), factory(str.substr(i + 1, str.length() - i - 1)));
			default: return nullptr;
			}
		}
	}
}

BooleanExpressionHandler::BooleanExpressionHandler(const std::string& str)
{
	expression = factory(str);
}

BooleanExpressionHandler::BooleanExpressionHandler(const BooleanExpressionHandler& other)
{
	copyFrom(other);
}

BooleanExpressionHandler::BooleanExpressionHandler(BooleanExpressionHandler&& other) noexcept
{
	moveFrom(std::move(other));
}

BooleanExpressionHandler& BooleanExpressionHandler::operator=(const BooleanExpressionHandler& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

BooleanExpressionHandler& BooleanExpressionHandler::operator=(BooleanExpressionHandler&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

BooleanExpressionHandler::~BooleanExpressionHandler()
{
	free();
}

bool BooleanExpressionHandler::isTautology() const
{
	return checkAllTruthÀssignments(expression, true);
}

bool BooleanExpressionHandler::isContradiction() const
{
	return checkAllTruthÀssignments(expression, false);
}

bool BooleanExpressionHandler::evaluate(const BooleanInterpretation& interpret) const
{
	return expression->evaluate(interpret);
}

void BooleanExpressionHandler::copyFrom(const BooleanExpressionHandler& other)
{
	expression = other.expression->clone();
}

void BooleanExpressionHandler::moveFrom(BooleanExpressionHandler&& other)
{
	expression = other.expression;
	other.expression = nullptr;
}

void BooleanExpressionHandler::free()
{
	delete expression;
	expression = nullptr;
}