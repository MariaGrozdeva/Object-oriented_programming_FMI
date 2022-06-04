#pragma once
#include "../FigureBase/Figure.h"

class Queen : public Figure
{
public:
	Queen(bool isWhite);

	bool canBeMoved(size_t currentX, size_t currentY, size_t destX, size_t destY) const;
	void print() const;
};