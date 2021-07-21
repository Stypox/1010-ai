#include "resources.hpp"

namespace app {

const app::Resource<sf::Font> Resources::font{[]() {
	sf::Font f;
	if (!f.loadFromFile("./res/SatellaRegular-ZVVaz.ttf")) {
		throw std::runtime_error("Could not load font");
	}
	return f;
}};

} // namespace app