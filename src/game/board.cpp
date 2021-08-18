#include "board.hpp"

#include <cassert>
#include <vector>
#include <algorithm>

#include "piece.hpp"
#include "app/constants.hpp"
#include "raw/raw_board.hpp"

namespace game {

int Board::clearFullLinesAndColumns() {
	std::vector<int> fullLines, fullColumns;
	for (int i = 0; i < app::BOARD_SIZE; ++i) {
		if (std::all_of(data[i].begin(), data[i].end(), [](piece_id_t id) { return id != pieceNone.id; })) {
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


Board::Board()
		: data{} {}

Board::Board(const std::array<std::array<piece_id_t, app::BOARD_SIZE>, app::BOARD_SIZE>& data)
		: data{data} {}


const std::array<std::array<piece_id_t, app::BOARD_SIZE>, app::BOARD_SIZE>& Board::getData() const {
	return data;
}

const raw_board_t& Board::getRawData() const {
	return rawData;
}


sf::Color Board::colorAt(board_index_t i, board_index_t j) const {
	return allPieces[data[i][j]].color;
}

bool Board::fitsPieceAt(board_index_t i, board_index_t j, piece_id_t id) const {
	return raw::fitsPieceAt(rawData, i, j, id);
}

bool Board::fitsPieceAnywhere(piece_id_t id) const {
	const Piece& piece = allPieces[id];
	for (board_index_t i = 0; i < app::BOARD_SIZE - piece.height + 1; ++i) {
		for (board_index_t j = 0; j < app::BOARD_SIZE - piece.width + 1; ++j) {
			if (fitsPieceAt(i, j, id)) {
				return true;
			}
		}
	}
	return false;
}

int Board::placePieceAt(board_index_t i, board_index_t j, piece_id_t id) {
	const Piece& piece = allPieces[id];
	int points = 0;
	for (board_index_t a = 0; a < piece.height; ++a) {
		for (board_index_t b = 0; b < piece.width; ++b) {
			if (piece.bitmask[a][b]) {
				++points;
				data[a + i][b + j] = piece.id;
			}
		}
	}

	points += clearFullLinesAndColumns();
	assert(raw::placePieceAt(rawData, i, j, id) == points);
	return points;
}

} // namespace game