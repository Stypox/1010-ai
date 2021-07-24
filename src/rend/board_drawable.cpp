#include "board_drawable.hpp"

#include "app/constants.hpp"

namespace rend {

constexpr float squareSpacing = app::SQUARE_SIZE + app::SQUARE_PADDING * 2;
constexpr float xBoard = app::LEFT_SECTION_WIDTH
	+ (app::RIGHT_SECTION_WIDTH - squareSpacing * game::Board::BOARD_SIZE) / 2.0f;
constexpr float yBoard =
	(app::WINDOW_HEIGHT - squareSpacing * game::Board::BOARD_SIZE) / 2.0f;

BoardDrawable::BoardDrawable() {
	for (int i = 0; i < game::Board::BOARD_SIZE; ++i) {
		for (int j = 0; j < game::Board::BOARD_SIZE; ++j) {
			rectangles[i][j].setSize({app::SQUARE_SIZE, app::SQUARE_SIZE});
			rectangles[i][j].setPosition(xBoard + app::SQUARE_PADDING + squareSpacing * j,
										 yBoard + app::SQUARE_PADDING + squareSpacing * i);
		}
	}

	updateBoard({});
}

std::tuple<int, int, bool> BoardDrawable::getSquareAtPixel(float x, float y) {
	if (x < xBoard || y < yBoard
			|| x > xBoard + squareSpacing * game::Board::BOARD_SIZE
			|| y > yBoard + squareSpacing * game::Board::BOARD_SIZE) {
		return {game::Board::BOARD_SIZE, game::Board::BOARD_SIZE, false};
	} else {
		return {(x - xBoard) / squareSpacing, (y - yBoard) / squareSpacing, true};
	}
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