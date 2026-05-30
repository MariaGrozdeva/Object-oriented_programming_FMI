#pragma once
#include "../Figure/Figure.h"

class Pawn : public Figure
{
private:
	mutable bool isFirstMove;

public:
	Pawn(bool isWhite);

	virtual bool canBeMoved(unsigned int currentX, unsigned int currentY, unsigned int destX, unsigned int destY) const override;
	virtual void print() const override;

	void setIsFirstMove();
};