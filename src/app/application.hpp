#pragma once

#include <SFML/Graphics.hpp>

namespace app {

class Application {

	sf::RenderWindow window;

	void drawUi();

public:
	void run();
};

} // namespace app