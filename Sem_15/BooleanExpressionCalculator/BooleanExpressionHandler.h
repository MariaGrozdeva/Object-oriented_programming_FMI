#pragma once
#include <iostream>
#include <string>
#include <string_view>

class BooleanInterpretation
{
private:
	uint32_t variables = 0;

public:
	bool operator()(char ch) const;
	void set(char ch, bool value);

	static bool isValid(char ch);
	static BooleanInterpretation createFromMask(uint32_t mask, uint32_t variables);
};

class BooleanExpressionHandler
{
private:
	class BooleanExpression
	{
	public:
		virtual bool evaluate(const BooleanInterpretation& interpret) const = 0;
		virtual void markUsedCharacters(uint32_t& usedCharacters) const = 0;
		virtual BooleanExpression* clone() const = 0;
		virtual ~BooleanExpression() = default;
	};

	class Variable final : public BooleanExpression
	{
	private:
		char ch;

	public:
		Variable(char ch);
		bool evaluate(const BooleanInterpretation& interpret) const override;
		void markUsedCharacters(uint32_t& usedCharacters) const override;
		BooleanExpression* clone() const override;
	};

	class UnaryExpression : public BooleanExpression
	{
	protected:
		BooleanExpression* expression;

	public:
		UnaryExpression(BooleanExpression* expression);
		void markUsedCharacters(uint32_t& usedCharacters) const override;
		~UnaryExpression();
	};

	class Negation final : public UnaryExpression
	{
	public:
		Negation(BooleanExpression* expression);
		bool evaluate(const BooleanInterpretation& interpret) const override;
		BooleanExpression* clone() const override;
	};

	class BinaryExpression : public BooleanExpression
	{
	protected:
		BooleanExpression* lhs;
		BooleanExpression* rhs;

	public:
		BinaryExpression(BooleanExpression* lhs, BooleanExpression* rhs);
		void markUsedCharacters(uint32_t& usedCharacters) const override;
		~BinaryExpression();
	};

	class Conjunction final : public BinaryExpression
	{
	public:
		Conjunction(BooleanExpression* lhs, BooleanExpression* rhs);
		bool evaluate(const BooleanInterpretation& interpret) const override;
		BooleanExpression* clone() const override;
	};

	class Disjunction final : public BinaryExpression
	{
	public:
		Disjunction(BooleanExpression* lhs, BooleanExpression* rhs);
		bool evaluate(const BooleanInterpretation& interpret) const override;
		BooleanExpression* clone() const override;
	};

	class Implication final : public BinaryExpression
	{
	public:
		Implication(BooleanExpression* lhs, BooleanExpression* rhs);
		bool evaluate(const BooleanInterpretation& interpret) const override;
		BooleanExpression* clone() const override;
	};

	class BiImplication final : public BinaryExpression
	{
	public:
		BiImplication(BooleanExpression* lhs, BooleanExpression* rhs);
		bool evaluate(const BooleanInterpretation& interpret) const override;
		BooleanExpression* clone() const override;
	};

	class Xor final : public BinaryExpression
	{
	public:
		Xor(BooleanExpression* lhs, BooleanExpression* rhs);
		bool evaluate(const BooleanInterpretation& interpret) const override;
		BooleanExpression* clone() const override;
	};

	BooleanExpression* expression = nullptr;

	static bool checkAllTruth¿ssignments(const BooleanExpression* expression, bool expected);

	BooleanExpression* factory(std::string_view str);

public:
	BooleanExpressionHandler(const std::string& str);
	BooleanExpressionHandler(const BooleanExpressionHandler& other);
	BooleanExpressionHandler(BooleanExpressionHandler&& other) noexcept;
	BooleanExpressionHandler& operator=(const BooleanExpressionHandler& other);
	BooleanExpressionHandler& operator=(BooleanExpressionHandler&& other) noexcept;
	~BooleanExpressionHandler();

	bool isTautology() const;
	bool isContradiction() const;
	bool evaluate(const BooleanInterpretation& interpret) const;

private:
	void copyFrom(const BooleanExpressionHandler& other);
	void moveFrom(BooleanExpressionHandler&& other);
	void free();
};