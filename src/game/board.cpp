#include "board.hpp"

#include "piece.hpp"
#include "app/constants.hpp"

namespace game {

Board::Board() {
	for (auto&& a : data) {
		std::fill(a.begin(), a.end(), allPieces.size()); // = no piece
	}
}

sf::Color Board::colorAt(int x, int y) const {
	if (data[x][y] < allPieces.size()) {
		return allPieces[data[x][y]].color;
	}
	return app::COLOR_PIECE_NONE;
}

} // namespace game