#include "ExpressionCalculator.h"

int main()
{
	ExpressionCalculator tautologyExpr("(Pv(!P))");
	ExpressionCalculator contradictionExpr("(P^(!P))");

	std::cout << tautologyExpr.isTautology() << std::endl;
	std::cout << tautologyExpr.isContradiction() << std::endl;

	std::cout << contradictionExpr.isTautology() << std::endl;
	std::cout << contradictionExpr.isContradiction() << std::endl;
}