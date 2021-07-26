#pragma once

#include <SFML/Graphics.hpp>

#include "rend/drawable.hpp"
#include "game/game.hpp"

namespace rend {

class Ui : Drawable {

	sf::Text titleText;
	sf::Text scoreText;

	sf::RectangleShape rightRectangle;
	sf::Text youLostText;
	sf::Text playAgainText;

	void updateScore(unsigned int score);
	void updateHasLost(bool hasLost, unsigned int score);

public:
	Ui();

	void updateGame(const game::Game& game);
	void draw(sf::RenderWindow& window) override;
};

} // namespace rend