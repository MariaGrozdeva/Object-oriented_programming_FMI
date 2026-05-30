#include "Queen.h"
#include <cmath>

Queen::Queen(bool isWhite) : Figure(isWhite, FigureType::QueenFigure)
{}

bool Queen::canBeMoved(unsigned int currentX, unsigned int currentY, unsigned int destX, unsigned int destY) const
{
	return (abs((int)currentX - (int)destX) == abs((int)currentY - (int)destY)) || (currentX == destX || currentY == destY);
}
void Queen::print() const
{
	getIsWhite() ? std::cout << 'Q' : std::cout << 'q';
}