#pragma once
#include "../Figures/Figure/Figure.h"

class FigureFactory
{
public:
	Figure* createFigure(bool isWhite, Figure::FigureType type) const;
};