#pragma once

#include "game/piece.hpp"

namespace ai {

struct Move {
	int i;
	int j;
	piece_id_t id;
};

} // namespace ai