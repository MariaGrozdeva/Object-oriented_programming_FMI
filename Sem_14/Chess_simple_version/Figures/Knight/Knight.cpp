#include "Knight.h"

Knight::Knight(bool isWhite) : Figure(isWhite, FigureType::KnightFigure)
{}

bool Knight::canBeMoved(size_t currentX, size_t currentY, size_t destX, size_t destY) const
{
	int xMovеment[] = { 1, 1, -1, -1, 2, -2, 2, -2 };
	int yMovеment[] = { 2, -2, 2, -2, 1, 1, -1, -1 };

	for (size_t i = 0; i < 8; i++)
		if (currentX + xMovеment[i] == destX && currentY + yMovеment[i] == destY)
			return true;

	return false;
}
void Knight::print() const
{
	getIsWhite() ? std::cout << 'K' : std::cout << 'k';
}