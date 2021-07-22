#include "board_drawable.hpp"

#include "app/constants.hpp"

namespace rend {

BoardDrawable::BoardDrawable() {
	constexpr float rectangleSpacing = app::RECTANGLE_SIZE + app::RECTANGLE_PADDING * 2;
	constexpr float xBoard = app::LEFT_SECTION_WIDTH
		+ (app::RIGHT_SECTION_WIDTH - rectangleSpacing * game::Board::BOARD_SIZE) / 2.0f;
	constexpr float yBoard =
		(app::WINDOW_HEIGHT - rectangleSpacing * game::Board::BOARD_SIZE) / 2.0f;

	for (int i = 0; i < game::Board::BOARD_SIZE; ++i) {
		for (int j = 0; j < game::Board::BOARD_SIZE; ++j) {
			rectangles[i][j].setSize({app::RECTANGLE_SIZE, app::RECTANGLE_SIZE});
			rectangles[i][j].setPosition(xBoard + app::RECTANGLE_PADDING + rectangleSpacing * j,
										 yBoard + app::RECTANGLE_PADDING + rectangleSpacing * i);
		}
	}

	updateBoard({});
}

void BoardDrawable::updateBoard(const game::Board& board) {
	for (int i = 0; i < game::Board::BOARD_SIZE; ++i) {
		for (int j = 0; j < game::Board::BOARD_SIZE; ++j) {
			rectangles[i][j].setFillColor(board.colorAt(i, j));
		}
	}
}

void BoardDrawable::draw(sf::RenderWindow& window)  {
	for (int i = 0; i < game::Board::BOARD_SIZE; ++i) {
		for (int j = 0; j < game::Board::BOARD_SIZE; ++j) {
			window.draw(rectangles[i][j]);
		}
	}
}

} // namespace rend