#pragma once

#include <functional>

#include "game/board.hpp"

namespace ai {

// the numerator represents how valuable it is to have an available space for that piece
// the denominator is the maximum number of occourrences of the piece
const std::vector<std::pair<game::Piece::id_t, float>> fullScoringTable {
	std::pair<game::Piece::id_t, float> // needs to be specified for the first item
	{game::pieceLong5Vertical.id,   0.25f /  60},
	{game::pieceLong4Vertical.id,   0.15f /  70},
	{game::pieceLong3Vertical.id,   0.07f /  80},
	{game::pieceLong2Vertical.id,   0.03f /  90},
	{game::pieceLong5Horizontal.id, 0.25f /  60},
	{game::pieceLong4Horizontal.id, 0.15f /  70},
	{game::pieceLong3Horizontal.id, 0.07f /  80},
	{game::pieceLong2Horizontal.id, 0.03f /  90},
	{game::pieceSquare3x3.id,       1.00f /  64},
	{game::pieceSquare2x2.id,       0.50f /  81},
	{game::pieceAngle3x3TL.id,      0.20f /  64},
	{game::pieceAngle3x3TR.id,      0.20f /  64},
	{game::pieceAngle3x3BR.id,      0.20f /  64},
	{game::pieceAngle3x3BL.id,      0.20f /  64},
	{game::pieceAngle2x2TL.id,      0.10f /  81},
	{game::pieceAngle2x2TR.id,      0.10f /  81},
	{game::pieceAngle2x2BR.id,      0.10f /  81},
	{game::pieceAngle2x2BL.id,      0.10f /  81},
	{game::pieceSingle.id,          0.05f / 100},
};

const std::vector<std::pair<game::Piece::id_t, float>> fastScoringTable {
	std::pair<game::Piece::id_t, float> // needs to be specified for the first item
	{game::pieceLong5Vertical.id,   0.25f /  60},
	{game::pieceLong5Horizontal.id, 0.25f /  60},
	{game::pieceSquare3x3.id,       1.00f /  64},
	{game::pieceSquare2x2.id,       0.50f /  81},
	{game::pieceAngle3x3TL.id,      0.10f /  64},
	{game::pieceAngle3x3TR.id,      0.10f /  64},
	{game::pieceAngle3x3BR.id,      0.10f /  64},
	{game::pieceAngle3x3BL.id,      0.10f /  64},
	{game::pieceSingle.id,          0.05f / 100},
};

// scoring functions should return a score > 0, so that it compares better than
// the base cases used in evaluation loops (where bestScoreSoFar starts at 0)

class FittingPiecesScoringFunction {
	const std::vector<std::pair<game::Piece::id_t, float>> scoringTable;

public:
	FittingPiecesScoringFunction(const std::vector<std::pair<game::Piece::id_t, float>>& scoringTable);

	float operator()(const game::Board& board) const;
};

class ConnectedComponentsScoringFunction {
	const float maxScore;
	const int penalizeSmallerThan;

public:
	ConnectedComponentsScoringFunction(float maxScore, int penalizeSmallerThan);

	float operator()(const game::Board& board) const;
};

std::function<float(const game::Board&)> operator+(
		const std::function<float(const game::Board&)>& first,
		const std::function<float(const game::Board&)>& second);

} // namespace ai