#pragma once

#include "game/piece.hpp"

namespace ai {

struct Move {
	int i;
	int j;
	game::Piece::id_t id;
};

} // namespace ai