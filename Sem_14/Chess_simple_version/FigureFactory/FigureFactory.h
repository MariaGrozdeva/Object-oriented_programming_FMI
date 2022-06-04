#pragma once
#include "../Figures/FigureBase/Figure.h"

class FigureFactory
{
public:
    Figure* createFigure(bool isWhite, Figure::FigureType type);
};