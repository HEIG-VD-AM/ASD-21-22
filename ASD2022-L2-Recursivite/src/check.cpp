#include "check.h"
#include "piece_manip.h"
bool checkNewPiece(const Board& board, const Piece& newPiece, std::size_t x, std::size_t y, Rotation r) {
	if (x == 0 && y == 0) return true; // base case (upper left corner)
	auto piece = getRotatedPiece(newPiece, r);
	int p1, p2;
	int currentPiece1, currentPiece2;

	if (x == 0 && y > 0 && piece[3] + 1 <= 8) {
		p1 = getRotatedPiece(PIECES[board[x][y - 1].pieceNo], board[x][y - 1].orientation)[1] + 1;
		currentPiece1 = piece[3] + 1;
	} else if (x > 0 && y == 0 && piece[0] + 1 <= 8) {
		p1 = getRotatedPiece(PIECES[board[x - 1][y].pieceNo], board[x - 1][y].orientation)[2] + 1;
		currentPiece1 = piece[0] + 1;
	} else {
		if (piece[0] + 1 > 8 || piece[3] + 1 > 8) return false;
		p1 = getRotatedPiece(PIECES[board[x][y - 1].pieceNo], board[x][y - 1].orientation)[1] + 1;
		p2 = getRotatedPiece(PIECES[board[x - 1][y].pieceNo], board[x - 1][y].orientation)[2] + 1;
		currentPiece1 = piece[3] + 1;
		currentPiece2 = piece[0] + 1;
	}
	if ((x == 0 && y > 0) || (x > 0 && y == 0)) { // simple cases (left OR up)
		return ((currentPiece1 % 2 == 0 && currentPiece1 - 1 == p1)
				|| (currentPiece1 % 2 != 0 && currentPiece1 + 1 == p1));
	} else { // general check (left and up)
		return (((currentPiece1 % 2 == 0 && currentPiece1 - 1 == p1)
				 || (currentPiece1 % 2 != 0 && currentPiece1 + 1 == p1))) &&
			   (((currentPiece2 % 2 == 0 && currentPiece2 - 1 == p2)
				 || (currentPiece2 % 2 != 0 && currentPiece2 + 1 == p2)));
	}
}