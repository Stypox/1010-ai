#pragma once

#include <SFML/Graphics.hpp>

namespace util {

sf::Text buildText(const unsigned int characterSize);

void setOriginAtCenter(sf::Text& text);

} // namespace util