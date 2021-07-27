#include "ui.hpp"

#include "util/graphics.hpp"
#include "util/string.hpp"
#include "app/constants.hpp"

namespace rend {

void Ui::updateScore(unsigned int score) {
	scoreText.setString(util::format(app::STRING_POINTS, score));
	util::setOriginAtCenter(scoreText);
    scoreText.setPosition(app::LEFT_SECTION_WIDTH / 2, 55);
}

void Ui::updateHasLost(bool hasLost, unsigned int score) {
	if (hasLost) {
		youLostText.setString(util::format(app::STRING_YOU_LOST, score));
		playAgainText.setString(app::STRING_PLAY_AGAIN);

		util::setOriginAtCenter(youLostText);
		util::setOriginAtCenter(playAgainText);

		constexpr float xText = app::WINDOW_WIDTH - app::RIGHT_SECTION_WIDTH / 2;
		constexpr float boardHeight = app::BOARD_SIZE * app::SQUARE_SIZE
			+ 2 * (app::BOARD_SIZE - 1) * app::SQUARE_PADDING;
		constexpr float textDistanceFromBorder = (app::WINDOW_HEIGHT - boardHeight) / 4.0f;
		youLostText.setPosition(xText, textDistanceFromBorder);
		playAgainText.setPosition(xText, app::WINDOW_HEIGHT - textDistanceFromBorder);

	} else {
		youLostText.setString("");
		playAgainText.setString("");
	}
}

Ui::Ui() :
		titleText{util::buildText(app::HEADER_CHARACTER_SIZE)},
		scoreText{util::buildText(app::SUBHEADER_CHARACTER_SIZE)},
		youLostText{util::buildText(app::HEADER_CHARACTER_SIZE)},
		playAgainText{util::buildText(app::HEADER_CHARACTER_SIZE)} {
	titleText.setString(app::STRING_TITLE);
	util::setOriginAtCenter(titleText);
    titleText.setPosition(app::LEFT_SECTION_WIDTH / 2, 30);

	updateScore(0);

	rightRectangle.setSize({app::RIGHT_SECTION_WIDTH, app::WINDOW_HEIGHT});
    rightRectangle.setPosition(app::LEFT_SECTION_WIDTH, 0);
    rightRectangle.setFillColor(app::RIGHT_BACKGROUND_COLOR);

	updateHasLost(false, 0);
}

void Ui::updateGame(const game::Game& game) {
	updateScore(game.getScore());
	updateHasLost(game.hasLost(), game.getScore());
}

void Ui::draw(sf::RenderWindow& window) {
	window.draw(titleText);
	window.draw(scoreText);
	window.draw(rightRectangle);
	window.draw(youLostText);
	window.draw(playAgainText);
}

} // namespace rend