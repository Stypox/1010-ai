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
	Application(const game::Game& game);

	void run();
};

} // namespace app