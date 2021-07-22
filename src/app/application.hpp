#pragma once

#include <SFML/Graphics.hpp>

#include "rend/ui.hpp"
#include "rend/board_drawable.hpp"

namespace app {

class Application {

	sf::RenderWindow window;
	rend::Ui ui;
	rend::BoardDrawable boardDrawable;

	void draw();

public:
	void run();
};

} // namespace app