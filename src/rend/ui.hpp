#pragma once

#include <SFML/Graphics.hpp>

#include "rend/drawable.hpp"

namespace rend {

class Ui : Drawable {

	sf::Text titleText;
	sf::Text scoreText;
	sf::RectangleShape rightRectangle;

public:
	Ui();

	void updateScore(const unsigned int newScore);
	void draw(sf::RenderWindow& window) override;
};

} // namespace rend