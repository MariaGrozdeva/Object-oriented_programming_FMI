#pragma once
#include "MyString/MyString.h"

class ExpressionCalculator
{
private:
	static const short alphabetSize = 26;

	class BooleanInterpretation
	{
	private:
		bool variables[alphabetSize] = { false };

	public:
		void setValue(char ch, bool value);
		bool getValue(char ch) const;

		static bool isValidCharacter(char ch);
		static BooleanInterpretation createFromNumber(unsigned number, const bool* variables);
	};

	class BooleanExpression
	{
	public:
		bool variables[alphabetSize] = { false };
		size_t variablesCount = 0;

		virtual bool evaluate(const BooleanInterpretation& interpretation) const = 0;
		virtual BooleanExpression* clone() const = 0;
		virtual ~BooleanExpression() = default;
	};

	class Variable : public BooleanExpression
	{
	private:
		char ch;

	public:
		Variable(char ch);

		bool evaluate(const BooleanInterpretation& interpretation) const override;
		BooleanExpression* clone() const override;
	};

	class UnaryExpression : public BooleanExpression
	{
	private:
		char operand;
		BooleanExpression* expression;

	public:
		UnaryExpression(char operand, BooleanExpression* expression);

		bool evaluate(const BooleanInterpretation& interpretation) const;
		BooleanExpression* clone() const;
		~UnaryExpression();
	};

	class BinaryExpression : public BooleanExpression
	{
	private:
		char operand;
		BooleanExpression* left;
		BooleanExpression* right;

	public:
		BinaryExpression(char operand, BooleanExpression* left, BooleanExpression* right);

		bool evaluate(const BooleanInterpretation& interpretation) const;
		BooleanExpression* clone() const;
		~BinaryExpression();
	};

	BooleanExpression* expression = nullptr;

	static bool checkAllVariations(const BooleanExpression* expression, bool expectedValue);
	static BooleanExpression* parseExpression(const MyString& str);

public:
	ExpressionCalculator(const MyString& str);
	ExpressionCalculator(const ExpressionCalculator& other);
	ExpressionCalculator(ExpressionCalculator&& other) noexcept;
	ExpressionCalculator& operator=(const ExpressionCalculator& other);
	ExpressionCalculator& operator=(ExpressionCalculator&& other) noexcept;
	~ExpressionCalculator();

	bool isTautology() const;
	bool isContradiction() const;

private:
	void free();
	void copyFrom(const ExpressionCalculator& other);
	void moveFrom(ExpressionCalculator&& other);
};