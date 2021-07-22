#include "graphics.hpp"

#include "app/resources.hpp"
#include "app/constants.hpp"

namespace util {

sf::Text buildText(const std::string& text, const unsigned int characterSize) {
    sf::Text res;
    res.setFont(app::Resources::font.get());
    res.setLetterSpacing(app::LETTER_SPACING);
    res.setFillColor(app::TEXT_COLOR);
    res.setString(text);
    res.setCharacterSize(characterSize);
	return res;
}

void setOriginAtCenter(sf::Text& text) {
	const sf::FloatRect rect = text.getLocalBounds();
	text.setOrigin(rect.left + rect.width  / 2.0f,
				   rect.top  + rect.height / 2.0f);
}

} // namespace util