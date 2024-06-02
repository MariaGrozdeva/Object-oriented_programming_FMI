#include "Bishop.h"
#include <cmath>

Bishop::Bishop(bool isWhite) : Figure(isWhite, FigureType::BishopFigure)
{}

bool Bishop::canBeMoved(unsigned int currentX, unsigned int currentY, unsigned int destX, unsigned int destY) const
{
	return abs((int)currentX - (int)destX) == abs((int)currentY - (int)destY);
}
void Bishop::print() const
{
	getIsWhite() ? std::cout << 'B' : std::cout << 'b';
}