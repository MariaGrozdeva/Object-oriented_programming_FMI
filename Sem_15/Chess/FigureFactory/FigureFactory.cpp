#include "FigureFactory.h"
#include "../Figures/King/King.h"
#include "../Figures/Queen/Queen.h"
#include "../Figures/Bishop/Bishop.h"
#include "../Figures/Knight/Knight.h"
#include "../Figures/Rook/Rook.h"
#include "../Figures/Pawn/Pawn.h"

Figure* FigureFactory::createFigure(bool isWhite, Figure::FigureType type) const
{
	switch (type)
	{
	case Figure::FigureType::KingFigure:
		return new King(isWhite);
	case Figure::FigureType::QueenFigure:
		return new Queen(isWhite);
	case Figure::FigureType::KnightFigure:
		return new Knight(isWhite);
	case Figure::FigureType::BishopFigure:
		return new Bishop(isWhite);
	case Figure::FigureType::PawnFigure:
		return new Pawn(isWhite);
	case Figure::FigureType::RookFigure:
		return new Rook(isWhite);
	default:
		return nullptr;
	}
}