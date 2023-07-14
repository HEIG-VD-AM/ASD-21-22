#include "piece_manip.h"
#include <algorithm>

char rotationToString(const Rotation& r) {
	switch (r) {
		case Rotation::B:
			return 'b';
		case Rotation::C:
			return 'c';
		case Rotation::D:
			return 'd';
		case Rotation::A:
		default:
			return 'a';
	}
}

Piece getRotatedPiece(const Piece& p, const Rotation& r) {
	Piece rotated = p;
	switch(r) {
		case Rotation::B:
			std::rotate(rotated.begin(), rotated.begin() + 1, rotated.end());
			break;
		case Rotation::C:
			std::rotate(rotated.begin(), rotated.begin() + 2, rotated.end());
			break;
		case Rotation::D:
			std::rotate(rotated.begin(), rotated.begin() + 3, rotated.end());
			break;
		default:
			break;
	}
	return rotated;
}

std::string pieceToString(const PieceInfo& p) {
	return std::to_string(p.pieceNo + 1) + rotationToString(p.orientation);
}

std::string boardToString(const Board& b) {
	std::string s;
	for (auto row : b) {
		for (auto col : row) {
			s += pieceToString(col) + " ";
		}
	}
	return s;
}