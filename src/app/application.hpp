#pragma once

#include <SFML/Graphics.hpp>

const sf::Color backgroundColor = sf::Color{30, 30, 30};
const sf::Color textColor = sf::Color::White;

namespace app {

class Application {

	static sf::RenderWindow window;

	static void drawUi();

public:
	static void run();
};

}