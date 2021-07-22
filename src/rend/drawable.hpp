#pragma once

#include <SFML/Graphics.hpp>

namespace rend {

class Drawable {
public:
	virtual void draw(sf::RenderWindow& window) = 0;
};

} // namespace rend