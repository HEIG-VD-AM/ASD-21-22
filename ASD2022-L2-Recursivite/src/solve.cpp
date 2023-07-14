#include "solve.h"
#include "check.h"
#include <algorithm>

#include <iostream>

using namespace std;

std::vector<Board> solve(const Pieces& pieces) {
	std::vector<Board> answers{};
	Board b(3, std::vector<PieceInfo>(3, PieceInfo{Rotation::A, 10}));
	Pieces p = pieces;
	cout << "Nombre d'appels recursifs : " << solveBoard(b, p, answers) << endl;
	return answers;
}

size_t findFirstNone(const Board& board, size_t& x, size_t& y) {
	size_t count = 0;
	for (size_t i = 0; i < 3; ++i) {
		for (size_t j = 0; j < 3; ++j) {
			if (board[i][j].pieceNo == 10) { // not placed
				x = i;
				y = j;
				return count;
			} else {
				++count;
			}
		}
	}
	return count;
}

int solveBoard(Board& board, std::vector<Piece>& remainingPieces,
				std::vector<Board>& answers) {

   static int counter;
   counter++;

	// Trivial case
	if (remainingPieces.empty()) {
		answers.push_back(board);
		return 0;
	}
	size_t x, y; // pos of the first none piece
	findFirstNone(board, x, y);
	// General case
	for (size_t i = 0; i < remainingPieces.size(); ++i) {
		for (size_t j = 0; j < 4; ++j) {
			if (checkNewPiece(board, remainingPieces[i], x, y, (Rotation) j)) {
				auto r = remainingPieces;
				auto it = std::remove(r.begin(), r.end(), remainingPieces[i]);
				r.erase(it);
				auto no = (size_t) (std::distance(PIECES.begin(), std::find(PIECES.begin(), PIECES.end(),
																			remainingPieces[i])));
				board[x][y] = PieceInfo{(Rotation) j, no};
				solveBoard(board, r, answers);
				board[x][y] = PieceInfo{Rotation::A, 10};
			}
		}
	}
   return counter;
}