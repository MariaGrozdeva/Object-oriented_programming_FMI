#include "Pawn.h"

Pawn::Pawn(bool isWhite) : Figure(isWhite, FigureType::PawnFigure), isFirstMove(true)
{}

bool Pawn::canBeMoved(unsigned int currentX, unsigned int currentY, unsigned int destX, unsigned int destY) const
{
	if (getIsWhite())
	{
		return abs((int)currentX - (int)destX) <= 1 + isFirstMove && abs((int)currentY - (int)destY) <= 1;
	}
	else
	{
		return abs((int)currentX - (int)destX) <= 1 + isFirstMove && abs((int)currentY - (int)destY) <= 1;
	}
}
void Pawn::print() const
{
	getIsWhite() ? std::cout << 'P' : std::cout << 'p';
}

void Pawn::setIsFirstMove()
{
	this->isFirstMove = false;
}