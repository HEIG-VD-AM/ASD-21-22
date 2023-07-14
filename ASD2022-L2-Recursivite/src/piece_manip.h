#ifndef PIECE_MANIP_H
#define PIECE_MANIP_H

#include "pieces.h"
#include <vector>
#include <string>

enum class Rotation {
	A, // Initial
	B, // 1 shift left
	C, // 2 shifts left
	D  // 3 shifts left
};

struct PieceInfo {
	Rotation orientation;
	std::size_t pieceNo;
};

using Board = std::vector<std::vector<PieceInfo>>;

char rotationToString(const Rotation& r);
Piece getRotatedPiece(const Piece& p, const Rotation& r);
std::string pieceToString(const PieceInfo& p);
std::string boardToString(const Board& b);


#endif //PIECE_MANIP_H