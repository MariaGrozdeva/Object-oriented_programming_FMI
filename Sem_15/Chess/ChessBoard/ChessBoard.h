#pragma once
#include "../FigureFactory/FigureFactory.h"

class ChessBoard
{
private:
	const static size_t BOARD_SIZE = 8;
	FigureFactory factory;

	struct LastMove
	{
		unsigned int x, y, destX, destY;
		Figure* destFigurePtr = nullptr;
		bool canUndo = false;
	} lastMove;

	struct Cell
	{
		Figure* figure = nullptr;

		Cell() = default;
		Cell(const Cell& other) = delete;
		Cell& operator=(const Cell& other) = delete;
		~Cell()
		{
			delete figure;
		}

		bool isEmpty() const
		{
			return !figure;
		}
		void print() const
		{
			if (figure)
			{
				figure->print();
			}
			else
			{
				std::cout << ' ';
			}
		}
	};
	Cell board[BOARD_SIZE][BOARD_SIZE];

	enum class Direction
	{
		Up, Down, Left, Right, UpLeft, UpRight, DownLeft, DownRight, None
	};

private:
	std::pair<int, int> getNextPosition(unsigned int x, unsigned int y, Direction direction) const;
	Direction getDirection(unsigned int x, unsigned int y, unsigned int destX, unsigned int destY) const;

	bool areAllIntermediateFree(unsigned int x, unsigned int y, unsigned int destX, unsigned int destY) const;

	bool checkIfMovementOfAFigureCanEscapeCheck(unsigned int figureX, unsigned int figureY, bool isWhite);

	void getKingsCoordinates(unsigned int& kingX, unsigned int& kingY, bool isWhite) const;

	void makeAMove(unsigned int x, unsigned int y, unsigned int destX, unsigned int destY);

public:
	ChessBoard();

	bool isPlayerInCheck(bool isWhite) const;
	bool isPlayerInCheckmate(bool isWhite);

	bool isMovable(unsigned int x, unsigned int y, unsigned int destX, unsigned int destY, bool isWhite) const;
	bool moveFigure(unsigned int x, unsigned int y, unsigned int destX, unsigned int destY, bool isWhite);

	void undoMove();

	void print() const;
};