#pragma once

#include <vector>
#include <functional>

#include "ai/move.hpp"
#include "ai/scoring_function.hpp"
#include "game/board.hpp"
#include "raw/raw_board.hpp"
#include "raw/raw_piece.hpp"

namespace ai {

class Ai {
	const ai::scoring_function_t scoringFunction;

public:
	Ai(const ai::scoring_function_t& scoringFunction);

	std::vector<Move> bruteForce(const raw_board_t& board, std::vector<piece_id_t> availablePieces);
	std::vector<Move> bestCombinationOfSingleMoves(const raw_board_t& board, std::vector<piece_id_t> availablePieces);
};

} // namespace ai