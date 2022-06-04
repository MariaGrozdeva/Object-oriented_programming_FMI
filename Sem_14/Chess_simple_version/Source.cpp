#include "ChessBoard/ChessBoard.h"

int main()
{
	ChessBoard c;
	c.print();

	c.moveFigure(0, 1, 2, 0);
	c.print();
}