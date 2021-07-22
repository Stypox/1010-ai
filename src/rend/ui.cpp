#include "ui.hpp"

#include "util/graphics.hpp"
#include "util/string.hpp"
#include "app/constants.hpp"

namespace rend {

Ui::Ui() :
		titleText{util::buildText(app::HEADER_CHARACTER_SIZE)},
		pointsText{util::buildText(app::SUBHEADER_CHARACTER_SIZE)} {
	titleText.setString(app::STRING_TITLE);
	util::setOriginAtCenter(titleText);
    titleText.setPosition(app::LEFT_SECTION_WIDTH / 2, 30);

	setPoints(0);

	rightRectangle.setSize({app::RIGHT_SECTION_WIDTH, app::WINDOW_HEIGHT});
    rightRectangle.setPosition(app::LEFT_SECTION_WIDTH, 0);
    rightRectangle.setFillColor(app::RIGHT_BACKGROUND_COLOR);
}

void Ui::setPoints(const unsigned int points) {
	pointsText.setString(util::format(app::STRING_POINTS, points));
	util::setOriginAtCenter(pointsText);
    pointsText.setPosition(app::LEFT_SECTION_WIDTH / 2, 55);
}

void Ui::draw(sf::RenderWindow& window) {
	window.draw(titleText);
	window.draw(pointsText);
	window.draw(rightRectangle);
}

} // namespace rend