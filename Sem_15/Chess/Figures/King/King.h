#pragma once
#include "../Figure/Figure.h"

class King : public Figure
{
public:
	King(bool isWhite);

	virtual bool canBeMoved(unsigned int currentX, unsigned int currentY, unsigned int destX, unsigned int destY) const override;
	virtual void print() const override;
};