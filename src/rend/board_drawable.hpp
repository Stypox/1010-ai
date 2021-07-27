#pragma once

#include <array>
#include <SFML/Graphics.hpp>

#include "game/board.hpp"
#include "rend/drawable.hpp"
#include "app/constants.hpp"

namespace rend {

class BoardDrawable : Drawable {
	std::array<std::array<sf::RectangleShape, app::BOARD_SIZE>, app::BOARD_SIZE> rectangles;

public:
	BoardDrawable();

	// returns i, j, successful
	std::tuple<int, int, bool> getSquareAtPixel(float x, float y);

	void updateBoard(const game::Board& board);
	void draw(sf::RenderWindow& window) override;
};

} // namespace rend