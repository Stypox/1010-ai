#pragma once

#include <functional>

#include "game/board.hpp"

namespace ai {

using scoring_table_t = std::vector<std::pair<game::Piece::id_t, float>>;
extern const scoring_table_t fullScoringTable;
extern const scoring_table_t fastScoringTable;
extern const scoring_table_t customScoringTable;


// scoring functions should return a score > 0, so that it compares better than
// the base cases used in evaluation loops (where bestScoreSoFar starts at 0)

class FittingPiecesScoringFunction {
	const scoring_table_t scoringTable;

public:
	FittingPiecesScoringFunction(const scoring_table_t& scoringTable);

	float operator()(const game::Board& board) const;
};

class ConnectedComponentsScoringFunction {
	const float maxScore;
	const int penalizeSmallerThan;

public:
	ConnectedComponentsScoringFunction(float maxScore, int penalizeSmallerThan);

	float operator()(const game::Board& board) const;
};

class BiggestRectangleScoringFunction {
	const float maxScore;

public:
	BiggestRectangleScoringFunction(float maxScore);

	float operator()(const game::Board& board) const;
};

std::function<float(const game::Board&)> operator+(
		const std::function<float(const game::Board&)>& first,
		const std::function<float(const game::Board&)>& second);

} // namespace ai