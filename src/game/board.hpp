#pragma once

#include <cstdint>
#include <array>
#include <bitset>

#include "game/piece.hpp"
#include "app/constants.hpp"
#include "util/typedefs.hpp"

namespace game {

class Board {
	// default initializes to piece index 0, i.e. pieceNone
	std::array<std::array<piece_id_t, app::BOARD_SIZE>, app::BOARD_SIZE> data;
	raw_board_t rawData;

	int clearFullLinesAndColumns(); // returns # of points

public:
	Board();

	const std::array<std::array<piece_id_t, app::BOARD_SIZE>, app::BOARD_SIZE>& getData() const;
	const raw_board_t& getRawData() const;

	sf::Color colorAt(board_index_t i, board_index_t j) const;
	bool fitsPieceAt(board_index_t i, board_index_t j, piece_id_t id) const; // make sure to check before placePieceAt
	bool fitsPieceAnywhere(piece_id_t id) const;
	int placePieceAt(board_index_t i, board_index_t j, piece_id_t id); // returns # of points, check fitsPieceAt before
};

} // namespace game