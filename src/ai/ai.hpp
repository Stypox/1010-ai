#pragma once

#include <vector>
#include <functional>

#include "ai/move.hpp"
#include "ai/scoring_function.hpp"
#include "game/board.hpp"

namespace ai {

class Ai {
	const ai::scoring_function_t scoringFunction;

	std::pair<float, std::vector<Move>> bruteForceWithScore(const game::Board& board, const std::vector<game::Piece::id_t>& availablePieces);

public:
	Ai(const ai::scoring_function_t& scoringFunction);

	std::vector<Move> bruteForce(const game::Board& board, std::vector<game::Piece::id_t> availablePieces);
	std::vector<Move> bestCombinationOfSingleMoves(const game::Board& board, std::vector<game::Piece::id_t> availablePieces);
};

} // namespace ai