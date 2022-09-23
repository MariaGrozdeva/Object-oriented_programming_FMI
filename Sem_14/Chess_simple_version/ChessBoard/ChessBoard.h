#pragma once
#include "../FigureFactory/FigureFactory.h"

const size_t BOARD_SIZE = 8;

class ChessBoard
{
private:

	FigureFactory factory;

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
				figure->print();
			else
				std::cout << ' ';
		}
	};

	Cell board[BOARD_SIZE][BOARD_SIZE];

public:
	ChessBoard();
	ChessBoard(const ChessBoard& other) = delete;
	ChessBoard& operator=(const ChessBoard&) = delete;

	void moveFigure(size_t x, size_t y, size_t destX, size_t destY);
	void print() const;
};