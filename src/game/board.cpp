#include "board.hpp"

#include <vector>
#include <algorithm>

#include "piece.hpp"
#include "app/constants.hpp"

namespace game {

int Board::clearFullLinesAndColumns() {
	std::vector<int> fullLines, fullColumns;
	for (int i = 0; i < app::BOARD_SIZE; ++i) {
		if (std::all_of(data[i].begin(), data[i].end(), [](Piece::id_t id) { return id != pieceNone.id; })) {
			fullLines.push_back(i);
		}

		bool fullColumn = true;
		for (int j = 0; j < app::BOARD_SIZE; ++j) {
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
		points += app::BOARD_SIZE;
		std::fill(data[i].begin(), data[i].end(), pieceNone.id);
	}

	for (int j : fullColumns) {
		for (int i = 0; i < app::BOARD_SIZE; ++i) {
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

bool Board::fitsPieceAt(int i, int j, const Piece& piece) const {
	for (int a = 0; a < piece.bitmask.size(); ++a) {
		for (int b = 0; b < piece.bitmask[0].size(); ++b) {
			if (piece.bitmask[a][b]) {
				int boardi = a + i, boardj = b + j;
				if (boardi >= app::BOARD_SIZE || boardj >= app::BOARD_SIZE || data[boardi][boardj]) {
					return false;
				}
			}
		}
	}
	return true;
}

bool Board::fitsPieceAnywhere(const Piece& piece) const {
	for (int i = 0; i < app::BOARD_SIZE; ++i) {
		for (int j = 0; j < app::BOARD_SIZE; ++j) {
			if (fitsPieceAt(i, j, piece)) {
				return true;
			}
		}
	}
	return false;
}

int Board::placePieceAt(int i, int j, const Piece& piece) {
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