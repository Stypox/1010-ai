#include "board.hpp"

#include "piece.hpp"

namespace game {

sf::Color Board::colorAt(int x, int y) const {
	if (data[x][y] < allPieces.size()) {
		return allPieces[data[x][y]].color;
	}
	return sf::Color::White;
}

} // namespace game