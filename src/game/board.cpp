#include "board.hpp"

#include "piece.hpp"
#include "app/constants.hpp"

namespace game {

sf::Color Board::colorAt(int x, int y) const {
	return allPieces[data[x][y]].color;
}

} // namespace game