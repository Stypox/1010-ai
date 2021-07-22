#pragma once

#include <SFML/Graphics.hpp>

#include "rend/ui.hpp"

namespace app {

class Application {

	sf::RenderWindow window;
	rend::Ui ui;

	void draw();

public:
	void run();
};

} // namespace app