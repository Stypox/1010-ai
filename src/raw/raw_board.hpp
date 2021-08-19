#pragma once

#include "game/board.hpp"
#include "util/typedefs.hpp"

namespace raw {

bool fitsPieceAt(const raw_board_t& board, board_index_t i, board_index_t j, piece_id_t id);
bool fitsPieceAtNoBoundaryChecks(const raw_board_t& board, board_index_t i, board_index_t j, piece_id_t id);
board_index_t fitsHowManyTimes(const raw_board_t& board, piece_id_t id);
int placePieceAt(raw_board_t& board, board_index_t i, board_index_t j, piece_id_t id);

bool usedAt(const raw_board_t& board, board_index_t i, board_index_t j);
void printBoard(const raw_board_t& board);

} // namespace raw