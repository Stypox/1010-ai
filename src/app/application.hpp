#pragma once

#include <SFML/Graphics.hpp>

#include "rend/ui.hpp"
#include "game/game.hpp"

namespace app {

class Application {

	sf::RenderWindow window;
	rend::Ui ui;
	game::Game game;

	void draw();

public:
	void run();
};

} // namespace app