/*
* Implementation of a chess game including check, checkmate, etc.
* Author: Maria Grozdeva
*/

#include "ChessBoard/ChessBoard.h"

int main()
{
	ChessBoard chessBoard;
	chessBoard.print();
	std::cout << "RULES: " <<
		"Each player begins the game with sixteen pieces: each player's pieces comprise of one king, one queen, two rooks, two bishops, two knights and eight pawns. " << std::endl <<
		"One player, referred to as White, controls the white pieces and the other player, Black, controls the black pieces; White is always the first player to move. " << std::endl <<
		"When a player makes a move, he should write the coordinates of the figure he wants to move and the ones of the square where he wants to put the figure. " << std::endl <<
		"Coordinates are as follows: x in [1..8], y in [a..h]. Example move: \"2a 4a\"." << std::endl <<
		"Good luck!" << std::endl;

	bool isWhiteTurn = true;
	while (true)
	{
		std::cout << std::endl << (isWhiteTurn ? "White's turn!" : "Black's turn!") << std::endl;
		std::cout << "Enter coordinates: ";

		int x, y, destX, destY;
		while (true)
		{
			std::string fromWhere;
			std::string toWhere;
			std::cin >> fromWhere >> toWhere;

			x = fromWhere[0] - '1';
			y = fromWhere[1] - 'a';
			destX = toWhere[0] - '1';
			destY = toWhere[1] - 'a';

			if (x < 0 || y < 0 || x >= 8 || y >= 8 || destX < 0 || destY < 0 || destX >= 8 || destY >= 8 || 
				(x == destX && y == destY) || 
				!chessBoard.isMovable(x, y, destX, destY, isWhiteTurn))
			{
				std::cout << "Invalid coordinates! Enter again: ";
				continue;
			}

			bool moved = chessBoard.moveFigure(x, y, destX, destY, isWhiteTurn);
			if (!moved)
			{
				std::cout << "Invalid coordinates! Enter again: ";
				continue;
			}

			if (chessBoard.isPlayerInCheck(isWhiteTurn))
			{
				chessBoard.undoMove();
				std::cout << "Invalid coordinates! You will be in check! Enter again: ";
				continue;
			}
			if (chessBoard.isPlayerInCheck(!isWhiteTurn))
			{
				if (chessBoard.isPlayerInCheckmate(!isWhiteTurn))
				{
					std::cout << (isWhiteTurn ? "Checkmate, black!" : "Checkmate, white!") << std::endl;
					return 0;
				}
				std::cout << (isWhiteTurn ? "Black, you are in check!" : "White, you are in check!") << std::endl;
			}
			break;
		}

		chessBoard.print();
		isWhiteTurn = !isWhiteTurn;
	}
}