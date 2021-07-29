#include "scoring_function.hpp"

namespace ai {

FittingPiecesScoringFunction::FittingPiecesScoringFunction(
		const std::vector<std::pair<game::Piece::id_t, float>>& scoringTable)
		: scoringTable{scoringTable} {}

float FittingPiecesScoringFunction::operator()(const game::Board& board) const {
	float score = 0.0f;
	for (const auto& [id, partialScore] : scoringTable) {
		const game::Piece& piece = game::allPieces[id];
		for (int i = 0; i < app::BOARD_SIZE - piece.height + 1; ++i) {
			for (int j = 0; j < app::BOARD_SIZE - piece.width + 1; ++j) {
				if (board.fitsPieceAt(i, j, piece)) {
					score += partialScore;
				}
			}
		}
	}
	return score;
}

} // namespace ai