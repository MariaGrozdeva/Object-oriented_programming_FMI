#include "ChessBoard.h"
#include "../Figures/King/King.h"
#include "../Figures/Queen/Queen.h"
#include "../Figures/Bishop/Bishop.h"
#include "../Figures/Knight/Knight.h"
#include "../Figures/Rook/Rook.h"
#include "../Figures/Pawn/Pawn.h"
#include <cassert>

std::pair<int, int> ChessBoard::getNextPosition(unsigned int x, unsigned int y, Direction direction) const
{
	int dx = 0, dy = 0;

	if (direction == Direction::Up)
	{
		dx = 1;
	}
	else if (direction == Direction::Down)
	{
		dx = -1;
	}
	else if (direction == Direction::Left)
	{
		dy = -1;
	}
	else if (direction == Direction::Right)
	{
		dy = 1;
	}
	else if (direction == Direction::UpRight)
	{
		dx = 1;
		dy = 1;
	}
	else if (direction == Direction::DownRight)
	{
		dx = -1;
		dy = 1;
	}
	else if (direction == Direction::UpLeft)
	{
		dx = 1;
		dy = -1;
	}
	else if (direction == Direction::DownLeft)
	{
		dx = -1;
		dy = -1;
	}

	return std::make_pair(x + dx, y + dy);
}
ChessBoard::Direction ChessBoard::getDirection(unsigned int x, unsigned int y, unsigned int destX, unsigned int destY) const
{
	int dx = destX - x;
	int dy = destY - y;

	if (abs(dx) == abs(dy))
	{
		if (dx > 0 && dy > 0)
		{
			return Direction::UpRight;
		}
		else if (dx > 0 && dy < 0)
		{
			return Direction::UpLeft;
		}
		else if (dx < 0 && dy > 0)
		{
			return Direction::DownRight;
		}
		else if (dx < 0 && dy < 0)
		{
			return Direction::DownLeft;
		}
	}
	else if (dx == 0)
	{
		if (dy > 0)
		{
			return Direction::Right;
		}
		else
		{
			return Direction::Left;
		}
	}
	else if (dy == 0)
	{
		if (dx > 0)
		{
			return Direction::Up;
		}
		else
		{
			return Direction::Down;
		}
	}

	return Direction::None;
}

bool ChessBoard::areAllIntermediateFree(unsigned int x, unsigned int y, unsigned int destX, unsigned int destY) const
{
	if (board[x][y].figure->getType() == Figure::FigureType::KnightFigure) // Knights are the only pieces that can move over other pieces, so we don't care if there are intermediate figures
	{
		return true;
	}

	Direction direction = getDirection(x, y, destX, destY);
	int iterX = x, iterY = y;
	while (true)
	{
		auto currentPosition = getNextPosition(iterX, iterY, direction);
		iterX = currentPosition.first;
		iterY = currentPosition.second;
		if (iterX == destX && iterY == destY)
		{
			return true;
		}
		if (!board[iterX][iterY].isEmpty())
		{
			return false;
		}
	}
}

bool ChessBoard::checkIfMovementOfAFigureCanEscapeCheck(unsigned int figureX, unsigned int figureY, bool isWhite)
{
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		for (size_t j = 0; j < BOARD_SIZE; j++)
		{
			if (isMovable(figureX, figureY, i, j, isWhite))
			{
				moveFigure(figureX, figureY, i, j, isWhite);
				if (isPlayerInCheck(isWhite))
				{
					undoMove();
					continue;
				}
				undoMove();
				return true;
			}
		}
	}
	return false;
}

void ChessBoard::getKingsCoordinates(unsigned int& kingX, unsigned int& kingY, bool isWhite) const
{
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		for (size_t j = 0; j < BOARD_SIZE; j++)
		{
			if (!board[i][j].isEmpty() && board[i][j].figure->getIsWhite() == isWhite && board[i][j].figure->getType() == Figure::FigureType::KingFigure)
			{
				kingX = i;
				kingY = j;
				return;
			}
		}
	}
}

void ChessBoard::makeAMove(unsigned int x, unsigned int y, unsigned int destX, unsigned int destY)
{
	delete lastMove.destFigurePtr;
	lastMove = { x, y, destX, destY, board[destX][destY].figure, true };

	board[destX][destY].figure = board[x][y].figure;
	board[x][y].figure = nullptr;
}

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

bool ChessBoard::isPlayerInCheck(bool isWhite) const
{
	unsigned int kingX = 0, kingY = 0;
	getKingsCoordinates(kingX, kingY, isWhite);

	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		for (size_t j = 0; j < BOARD_SIZE; j++)
		{
			if (!board[i][j].isEmpty() && board[i][j].figure->getIsWhite() != isWhite)
			{
				if (isMovable(i, j, kingX, kingY, !isWhite))
				{
					return true;
				}
			}
		}
	}

	return false;
}
bool ChessBoard::isPlayerInCheckmate(bool isWhite)
{
	unsigned int kingX = 0, kingY = 0;
	getKingsCoordinates(kingX, kingY, isWhite);

	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		for (size_t j = 0; j < BOARD_SIZE; j++)
		{
			if (!board[i][j].isEmpty() && board[i][j].figure->getIsWhite() == isWhite &&
				checkIfMovementOfAFigureCanEscapeCheck(i, j, isWhite))
			{
				return false;
			}
		}
	}
	return true;
}

bool ChessBoard::isMovable(unsigned int x, unsigned int y, unsigned int destX, unsigned int destY, bool isWhite) const
{
	if (board[x][y].isEmpty() || board[x][y].figure->getIsWhite() != isWhite ||
		(!board[destX][destY].isEmpty() && board[destX][destY].figure->getIsWhite() == isWhite) ||
		!board[x][y].figure->canBeMoved(x, y, destX, destY) || !areAllIntermediateFree(x, y, destX, destY))
	{
		return false;
	}
	if (board[x][y].figure->getType() == Figure::FigureType::PawnFigure)
	{
		Pawn* pawn = dynamic_cast<Pawn*>(board[x][y].figure);
		if ((isWhite && (int)destX - (int)x > 0) || (!isWhite && (int)destX - (int)x < 0)) // pawns can move only forward
		{
			return false;
		}
		if (!(abs((int)y - (int)destY) == 0 && board[destX][destY].isEmpty() || // pawns can move forward only if these cells ARE vacant
			abs((int)y - (int)destY) == 1 && !board[destX][destY].isEmpty())) // pawns can move diagonally only if these cells ARE NOT vacant
		{
			return false;;
		}
	}
	return true;
}
bool ChessBoard::moveFigure(unsigned int x, unsigned int y, unsigned int destX, unsigned int destY, bool isWhite)
{
	if (!isMovable(x, y, destX, destY, isWhite))
	{
		return false;
	}

	if (board[x][y].figure->getType() == Figure::FigureType::PawnFigure)
	{
		Pawn* pawn = dynamic_cast<Pawn*>(board[x][y].figure);
		pawn->setIsFirstMove();
	}
	makeAMove(x, y, destX, destY);
	return true;
}

void ChessBoard::undoMove()
{
	assert(lastMove.canUndo);

	board[lastMove.x][lastMove.y].figure = board[lastMove.destX][lastMove.destY].figure;
	board[lastMove.destX][lastMove.destY].figure = lastMove.destFigurePtr;
	lastMove.destFigurePtr = nullptr;
	lastMove.canUndo = false;
}

void ChessBoard::print() const
{
	std::cout << std::endl;
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		for (size_t j = 0; j < BOARD_SIZE; j++)
		{
			std::cout << '|';
			board[i][j].print();
			if (j == BOARD_SIZE - 1)
			{
				std::cout << '|';
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}