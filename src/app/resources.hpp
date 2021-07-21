#pragma once

#include <SFML/Graphics.hpp>

#include "resource.hpp"

namespace app {

class Resources {

public:
	Resources() = delete;

	static const Resource<sf::Font> font;
};

} // namespace app