#pragma once

#include <array>
#include <bitset>

#include "game/piece.hpp"

namespace game {

class Board {
public:
	static constexpr int BOARD_SIZE = 10;

private:
	// default initializes to piece index 0, i.e. pieceNone
	std::array<std::array<Piece::id_t, BOARD_SIZE>, BOARD_SIZE> data;

	int clearFullLinesAndColumns(); // returns # of points

public:
	sf::Color colorAt(int i, int j) const;
	bool fitsPieceAt(int i, int j, const Piece& piece) const; // make sure to check before placePieceAt
	bool fitsPieceAnywhere(const Piece& piece) const;
	int placePieceAt(int i, int j, const Piece& piece); // returns # of points
};

} // namespace game