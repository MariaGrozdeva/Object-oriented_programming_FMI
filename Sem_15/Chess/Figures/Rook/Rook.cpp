#include "Rook.h"

Rook::Rook(bool isWhite) : Figure(isWhite, FigureType::RookFigure)
{}

bool Rook::canBeMoved(unsigned int currentX, unsigned int currentY, unsigned int destX, unsigned int destY) const
{
	return currentX == destX || currentY == destY;
}
void Rook::print() const
{
	getIsWhite() ? std::cout << 'R' : std::cout << 'r';
}