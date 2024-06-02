#include "King.h"
#include <cmath>

King::King(bool isWhite) : Figure(isWhite, FigureType::KingFigure)
{}

bool King::canBeMoved(unsigned int currentX, unsigned int currentY, unsigned int destX, unsigned int destY) const
{
	return abs((int)currentX - (int)destX) <= 1 && abs((int)currentY - (int)destY) <= 1;
}
void King::print() const
{
	getIsWhite() ? std::cout << 'K' : std::cout << 'k';
}