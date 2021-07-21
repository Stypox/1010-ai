#include "resources.hpp"

namespace app {

const app::Resource<sf::Font> Resources::font{[]() {
	sf::Font f;
	f.loadFromFile("");
	return f;
}};

} // namespace app