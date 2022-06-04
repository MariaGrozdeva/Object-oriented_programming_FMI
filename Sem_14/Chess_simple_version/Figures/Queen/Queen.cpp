#include "Queen.h"

Queen::Queen(bool isWhite) : Figure(isWhite, FigureType::QueenFigure)
{}

bool Queen::canBeMoved(size_t currentX, size_t currentY, size_t destX, size_t destY) const
{
	return (abs((int)currentX - (int)destX) == abs((int)currentY - (int)destY)) || (currentX == destX || currentY == destY);
}
void Queen::print() const
{
	getIsWhite() ? std::cout << 'Q' : std::cout << 'q';
}