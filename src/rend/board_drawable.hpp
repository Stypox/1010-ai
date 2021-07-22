#pragma once

#include <array>
#include <SFML/Graphics.hpp>

#include "game/board.hpp"
#include "rend/drawable.hpp"

namespace rend {

class BoardDrawable : Drawable {
	std::array<std::array<sf::RectangleShape, game::Board::BOARD_SIZE>, game::Board::BOARD_SIZE> rectangles;

public:
	BoardDrawable();

	void updateBoard(const game::Board& board);
	void draw(sf::RenderWindow& window) override;
};

} // namespace rend