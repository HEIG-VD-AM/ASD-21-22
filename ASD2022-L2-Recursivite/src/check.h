#ifndef CHECK_H
#define CHECK_H

#include "pieces.h"
#include "piece_manip.h"

bool checkNewPiece(const Board& board, const Piece& newPiece, std::size_t x,
				   std::size_t y, Rotation r);

#endif //CHECK_H
