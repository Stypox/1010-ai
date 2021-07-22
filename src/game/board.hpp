#pragma once

#include <array>
#include <bitset>

#include "game/piece.hpp"

namespace game {

class Board {
public:
	static constexpr int BOARD_SIZE = 10;

private:
	std::array<std::array<Piece::id_t, BOARD_SIZE>, BOARD_SIZE> data{{allPieces.size()}};

public:
	sf::Color colorAt(int x, int y) const;
};

} // namespace game