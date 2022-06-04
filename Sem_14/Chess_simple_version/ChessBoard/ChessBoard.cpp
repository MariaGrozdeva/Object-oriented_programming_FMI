#include "ChessBoard.h"

ChessBoard::ChessBoard()
{
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		board[1][i].figure = factory.createFigure(false, Figure::FigureType::PawnFigure);
		board[6][i].figure = factory.createFigure(true, Figure::FigureType::PawnFigure);
	}

	board[0][0].figure = factory.createFigure(false, Figure::FigureType::RookFigure);
	board[0][7].figure = factory.createFigure(false, Figure::FigureType::RookFigure);
	board[7][0].figure = factory.createFigure(true, Figure::FigureType::RookFigure);
	board[7][7].figure = factory.createFigure(true, Figure::FigureType::RookFigure);

	board[0][1].figure = factory.createFigure(false, Figure::FigureType::KnightFigure);
	board[0][6].figure = factory.createFigure(false, Figure::FigureType::KnightFigure);
	board[7][1].figure = factory.createFigure(true, Figure::FigureType::KnightFigure);;
	board[7][6].figure = factory.createFigure(true, Figure::FigureType::KnightFigure);

	board[0][2].figure = factory.createFigure(false, Figure::FigureType::BishopFigure);
	board[0][5].figure = factory.createFigure(false, Figure::FigureType::BishopFigure);;
	board[7][2].figure = factory.createFigure(true, Figure::FigureType::BishopFigure);
	board[7][5].figure = factory.createFigure(true, Figure::FigureType::BishopFigure);

	board[0][4].figure = factory.createFigure(false, Figure::FigureType::QueenFigure);
	board[7][4].figure = factory.createFigure(true, Figure::FigureType::QueenFigure);

	board[0][3].figure = factory.createFigure(false, Figure::FigureType::KingFigure);
	board[7][3].figure = factory.createFigure(true, Figure::FigureType::KingFigure);
}

void ChessBoard::moveFigure(size_t x, size_t y, size_t destX, size_t destY)
{
	Figure* current = board[x][y].figure;

	if (current->getType() == Figure::FigureType::PawnFigure)
	{
		// Some other logic.
	}
	else
	{
		if (board[x][y].figure && board[x][y].figure->canBeMoved(x, y, destX, destY))
		{
			delete board[destX][destY].figure;
			board[destX][destY].figure = board[x][y].figure;
			board[x][y].figure = nullptr;
		}
	}
}
void ChessBoard::print() const
{
	std::cout << "--------" << std::endl;
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		for (size_t j = 0; j < BOARD_SIZE; j++)
			board[i][j].print();
		std::cout << std::endl;
	}
	std::cout << "--------" << std::endl << std::endl << std::endl;
}