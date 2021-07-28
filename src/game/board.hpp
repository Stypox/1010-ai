#pragma once

#include <array>
#include <bitset>

#include "game/piece.hpp"
#include "app/constants.hpp"

namespace game {

class Board {
	// default initializes to piece index 0, i.e. pieceNone
	std::array<std::array<Piece::id_t, app::BOARD_SIZE>, app::BOARD_SIZE> data;

	int clearFullLinesAndColumns(); // returns # of points

public:
	sf::Color colorAt(int i, int j) const;
	bool fitsPieceAt(int i, int j, const Piece& piece) const; // make sure to check before placePieceAt
	bool fitsPieceAnywhere(const Piece& piece) const;
	int placePieceAt(int i, int j, const Piece& piece); // returns # of points, check fitsPieceAt before
};

} // namespace game