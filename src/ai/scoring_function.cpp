#include "scoring_function.hpp"

namespace ai {

FittingPiecesScoringFunction::FittingPiecesScoringFunction(
		const std::vector<std::pair<game::Piece::id_t, float>>& scoringTable)
		: scoringTable{scoringTable} {}

float FittingPiecesScoringFunction::operator()(const game::Board& board) const {
	float score = 0.01f; // always greater than 0, so that it compares better than the score used as the base case
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

float ConnectedComponentsScoringFunction::operator()(const game::Board& board) const {
	const auto& boardData = board.getData();
	std::array<std::bitset<app::BOARD_SIZE>, app::BOARD_SIZE> seen{}; // initialize to false

	std::function<void(int, int, bool)> dfs = [&boardData, &seen, &dfs](int i, int j, bool filled) {
		if (i < 0 || i >= app::BOARD_SIZE || j < 0 || j >= app::BOARD_SIZE
				|| seen[i][j] || filled != (boardData[i][j] == game::pieceNone.id)) {
			return;
		}

		seen[i][j] = true;
		dfs(i + 1, j,     filled);
		dfs(i - 1, j,     filled);
		dfs(i,     j + 1, filled);
		dfs(i,     j - 1, filled);
	};

	int connectedComponentsCount = 0;
	for (int i = 0; i < app::BOARD_SIZE; ++i) {
		for (int j = 0; j < app::BOARD_SIZE; ++j) {
			if (!seen[i][j]) {
				++connectedComponentsCount;
				dfs(i, j, boardData[i][j] == game::pieceNone.id);
			}
		}
	}

	return std::max(1.0f - 0.2f * connectedComponentsCount, 0.0f) + 0.2f / connectedComponentsCount;
}


std::function<float(const game::Board&)> combineScoringFunctions(
		const std::function<float(const game::Board&)>& first,
		const std::function<float(const game::Board&)>& second) {
	return [first, second](const game::Board& board) {
		return first(board) + second(board);
	};
}

} // namespace ai