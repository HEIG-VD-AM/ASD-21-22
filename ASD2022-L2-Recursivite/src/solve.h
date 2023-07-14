#ifndef SOLVE_H
#define SOLVE_H

#include "pieces.h"
#include <vector>
#include "piece_manip.h"



std::vector<Board> solve(const Pieces& pieces);

int solveBoard(Board& board, std::vector<Piece>& remainingPieces, std::vector<Board>& answers);
#endif //SOLVE_H
