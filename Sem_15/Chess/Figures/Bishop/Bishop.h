#pragma once
#include "../Figure/Figure.h"

class Bishop : public Figure
{
public:
	Bishop(bool isWhite);

	virtual bool canBeMoved(unsigned int currentX, unsigned int currentY, unsigned int destX, unsigned int destY) const override;
	virtual void print() const override;
};