#pragma once
#include <string>
#include <cassert>
#include <cstdint>

class SetCalculator
{
public:
	struct Element
	{
		bool sets[26] = { false };

		void set(char ch, bool isIn)
		{
			assert(ch >= 'A' && ch <= 'Z');
			sets[ch - 'A'] = isIn;
		}
		bool get(char ch) const
		{
			assert(ch >= 'A' && ch <= 'Z');
			return sets[ch - 'A'];
		}
	};

private:
	class SetExpression
	{
	public:
		virtual bool isElementIn(const Element& el) const = 0;
		virtual void markUsedVariables(uint32_t& used) const = 0;
		virtual SetExpression* clone() const = 0;
		virtual ~SetExpression() = default;
	};

	class Singleton final : public SetExpression
	{
	private:
		char name;

	public:
		Singleton(char name);
		bool isElementIn(const Element& el) const override;
		void markUsedVariables(uint32_t& used) const override;
		SetExpression* clone() const override;
	};

	class UnaryOperation final : public SetExpression
	{
	private:
		char op;
		SetExpression* sub;

	public:
		UnaryOperation(char op, SetExpression* sub);
		bool isElementIn(const Element& el) const override;
		void markUsedVariables(uint32_t& used) const override;
		SetExpression* clone() const override;
		~UnaryOperation();
	};

	class BinaryOperation final : public SetExpression
	{
	private:
		char op;
		SetExpression* left;
		SetExpression* right;

	public:
		BinaryOperation(char op, SetExpression* left, SetExpression* right);
		bool isElementIn(const Element& el) const override;
		void markUsedVariables(uint32_t& used) const override;
		SetExpression* clone() const override;
		~BinaryOperation();
	};

	SetExpression* ptr = nullptr;

	SetExpression* parse(const std::string& str);
	bool isOperation(char ch) const;

	static bool checkAllAssignments(const SetExpression* lhs, const SetExpression* rhs);
	static Element createFromMask(uint32_t mask, uint32_t used);

	void copyFrom(const SetCalculator& other);
	void free();

public:
	SetCalculator(const std::string& str);
	SetCalculator(const SetCalculator& other);
	SetCalculator& operator=(const SetCalculator& other);
	~SetCalculator();

	bool isElementIn(const Element& el) const;
	bool isSameSet(const SetCalculator& other) const;
};
