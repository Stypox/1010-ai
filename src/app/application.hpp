#pragma once

#include <SFML/Graphics.hpp>

namespace app {

class Application {

	static sf::RenderWindow window;

	static void drawUi();

public:
	Application() = delete;

	static void run();
};

} // namespace app