#pragma once

#include <SFML/Graphics.hpp>

#include "rend/drawable.hpp"

namespace rend {

class Ui : Drawable {

	unsigned int points;

	sf::Text titleText;
	sf::Text pointsText;
	sf::RectangleShape rightRectangle;

public:
	Ui();

	void setPoints(const unsigned int newPoints);
	void draw(sf::RenderWindow& window) override;
};

} // namespace rend