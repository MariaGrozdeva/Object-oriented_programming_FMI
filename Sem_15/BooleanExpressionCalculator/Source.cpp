#include "BooleanExpressionHandler.h"

int main()
{
	BooleanExpressionHandler expr("((p)|((q)&(t)))");

	BooleanInterpretation bi;
	bi.set('p', true);
	std::cout << expr.evaluate(bi) << std::endl;

	BooleanExpressionHandler expr2("((p)|(!(p)))");
	std::cout << expr2.isTautology() << std::endl;
}