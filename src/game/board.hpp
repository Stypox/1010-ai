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

public:
	sf::Color colorAt(int x, int y) const;
};

} // namespace game