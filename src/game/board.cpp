#include "board.hpp"

#include <vector>
#include <algorithm>

#include "piece.hpp"
#include "app/constants.hpp"

namespace game {

int Board::clearFullLinesAndColumns() {
	std::vector<int> fullLines, fullColumns;
	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (std::all_of(data[i].begin(), data[i].end(), [](Piece::id_t id) { return id != pieceNone.id; })) {
			fullLines.push_back(i);
		}

		bool fullColumn = true;
		for (int j = 0; j < BOARD_SIZE; ++j) {
			if (data[j][i] == pieceNone.id) {
				fullColumn = false;
				break;
			}
		}
		if (fullColumn) {
			fullColumns.push_back(i);
		}
	}

	int points = 0;
	for (int i : fullLines) {
		points += BOARD_SIZE;
		std::fill(data[i].begin(), data[i].end(), pieceNone.id);
	}

	for (int j : fullColumns) {
		for (int i = 0; i < BOARD_SIZE; ++i) {
			// it could already have been set to none by the
			// lines loop above, so don't count the point twice
			points += (data[i][j] != pieceNone.id);
			data[i][j] = pieceNone.id;
		}
	}

	return points;
}

sf::Color Board::colorAt(int i, int j) const {
	return allPieces[data[i][j]].color;
}

int Board::placePieceAt(int i, int j, const Piece& piece) {
	for (int a = 0; a < piece.bitmask.size(); ++a) {
		for (int b = 0; b < piece.bitmask[0].size(); ++b) {
			if (piece.bitmask[a][b]) {
				int boardi = a + i, boardj = b + j;
				if (boardi >= BOARD_SIZE || boardj >= BOARD_SIZE || data[boardi][boardj]) {
					return false;
				}
			}
		}
	}

	int points = 0;
	for (int a = 0; a < piece.bitmask.size(); ++a) {
		for (int b = 0; b < piece.bitmask[0].size(); ++b) {
			if (piece.bitmask[a][b]) {
				++points;
				data[a + i][b + j] = piece.id;
			}
		}
	}

	points += clearFullLinesAndColumns();
	return points;
}

} // namespace game