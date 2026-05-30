#include "Knight.h"

Knight::Knight(bool isWhite) : Figure(isWhite, FigureType::KnightFigure)
{}

bool Knight::canBeMoved(unsigned int currentX, unsigned int currentY, unsigned int destX, unsigned int destY) const
{
	static const unsigned int allPossibleMoves = 8;
	static const int xMovеment[] = { 1, 1, -1, -1, 2, -2, 2, -2 };
	static const int yMovеment[] = { 2, -2, 2, -2, 1, 1, -1, -1 };

	for (size_t i = 0; i < allPossibleMoves; i++)
	{
		if (currentX + xMovеment[i] == destX && currentY + yMovеment[i] == destY)
		{
			return true;
		}
	}
	return false;
}
void Knight::print() const
{
	getIsWhite() ? std::cout << 'N' : std::cout << 'n';
}