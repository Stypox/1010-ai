#pragma once

#include <vector>

#include "game/game.hpp"

namespace app {

class NoUiApplication {
	game::Game game;

public:
	NoUiApplication(const game::Game& game);

	void run();
};

} // namespace app
