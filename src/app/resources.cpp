#include "resources.hpp"

namespace app {

const app::Resource<sf::Font> Resources::font{[]() {
	sf::Font f;
	f.loadFromFile("./res/SatellaRegular-ZVVaz.ttf");
	return f;
}};

} // namespace app