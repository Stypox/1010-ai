#include "scoring_function.hpp"

#include <stack>
#include <iostream>

namespace ai {

// the numerator represents how valuable it is to have an available space for that piece
// the denominator is the maximum number of occourrences of the piece
const scoring_table_t fullScoringTable {
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

const scoring_table_t fastScoringTable {
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

const scoring_table_t customScoringTable {
	std::pair<game::Piece::id_t, float> // needs to be specified for the first item
	{game::pieceLong5Vertical.id,   0.25f /  60},
	{game::pieceLong4Vertical.id,   0.04f /  70},
	{game::pieceLong3Vertical.id,   0.02f /  80},
	{game::pieceLong5Horizontal.id, 0.30f /  60},
	{game::pieceLong4Horizontal.id, 0.04f /  70},
	{game::pieceLong3Horizontal.id, 0.02f /  80},
	{game::pieceSquare3x3.id,       1.00f /  64},
	{game::pieceSquare2x2.id,       0.20f /  81},
	{game::pieceAngle3x3TL.id,      0.05f /  64},
	{game::pieceAngle3x3TR.id,      0.05f /  64},
	{game::pieceAngle3x3BR.id,      0.05f /  64},
	{game::pieceAngle3x3BL.id,      0.07f /  64},
	{game::pieceSingle.id,          0.02f / 100},
};


FittingPiecesScoringFunction::FittingPiecesScoringFunction(
		const scoring_table_t& theScoringTable)
		: scoringTable{theScoringTable} {}

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

ConnectedComponentsScoringFunction::ConnectedComponentsScoringFunction(float maxScore, int penalizeSmallerThan)
		: maxScore{maxScore}, penalizeSmallerThan{penalizeSmallerThan} {}

float ConnectedComponentsScoringFunction::operator()(const game::Board& board) const {
	// basically bucket fill multiple times, runs in O(N*M)

	const auto& boardData = board.getData();
	std::array<std::bitset<app::BOARD_SIZE>, app::BOARD_SIZE> seen{}; // initialize to false

	std::function<int(int, int, bool)> dfs = [&boardData, &seen, &dfs](int i, int j, bool filled) {
		if (i < 0 || i >= app::BOARD_SIZE || j < 0 || j >= app::BOARD_SIZE
				|| seen[i][j] || filled != (boardData[i][j] == game::pieceNone.id)) {
			return 0;
		}

		seen[i][j] = true;
		return 1
			+ dfs(i + 1, j,     filled);
			+ dfs(i - 1, j,     filled);
			+ dfs(i,     j + 1, filled);
			+ dfs(i,     j - 1, filled);
	};

	int smallConnectedComponents = 0;
	for (int i = 0; i < app::BOARD_SIZE; ++i) {
		for (int j = 0; j < app::BOARD_SIZE; ++j) {
			if (!seen[i][j]) {
				int componentSize = dfs(i, j, boardData[i][j] == game::pieceNone.id);
				if (componentSize < penalizeSmallerThan) {
					++smallConnectedComponents;
				}
			}
		}
	}

	return maxScore * std::max(1.0f - 0.2f * smallConnectedComponents,
		0.2f / (smallConnectedComponents + 1));
}

BiggestRectangleScoringFunction::BiggestRectangleScoringFunction(float maxScore)
		: maxScore{maxScore} {}

float BiggestRectangleScoringFunction::operator()(const game::Board& board) const {
	// https://www.drdobbs.com/database/the-maximal-rectangle-problem/184410529
	// runs in O(N*M)

	const auto& boardData = board.getData();
	std::array<int, app::BOARD_SIZE + 1> spacesRight{}; // the last element will stay 0

	int bestArea = 0;
	for (int j = app::BOARD_SIZE - 1; j >= 0; --j) {
		// spacesRight will contain the number of spaces to the
		// right of each square in the current column (the j-th)
		for (int i = 0; i < app::BOARD_SIZE; ++i) {
			if (boardData[i][j] == game::pieceNone.id) {
				++spacesRight[i];
			} else {
				spacesRight[i] = 0;
			}
		}

		int prevSpacesRight = 0; // i.e. the width of the previous iteration
		std::stack<std::pair<int, int>> rectangles; // (startingLine, width (i.e. spacesRight))
		for (int i = 0; i < app::BOARD_SIZE + 1; ++i) {
			if (spacesRight[i] > prevSpacesRight) {
				rectangles.push({i, spacesRight[i]});
			} else {
				int lastStartingLine = -1;
				// pop from the stack all of the rectangles that do not fit anymore
				while (!rectangles.empty() && rectangles.top().second > spacesRight[i]) {
					auto [startingLine, width] = rectangles.top();
					rectangles.pop();
					bestArea = std::max(bestArea, (i - startingLine) * width); // calculate area
					lastStartingLine = startingLine;
				}

				if (lastStartingLine >= 0) {
					rectangles.push({lastStartingLine, spacesRight[i]});
				}
			}
			prevSpacesRight = spacesRight[i];
		}
	}

	return maxScore * bestArea / (app::BOARD_SIZE * app::BOARD_SIZE);
}


std::function<float(const game::Board&)> operator+(
		const std::function<float(const game::Board&)>& first,
		const std::function<float(const game::Board&)>& second) {
	return [first, second](const game::Board& board) {
		return first(board) + second(board);
	};
}

} // namespace ai