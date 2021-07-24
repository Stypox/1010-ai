#include "board.hpp"

#include "piece.hpp"
#include "app/constants.hpp"

namespace game {

sf::Color Board::colorAt(int i, int j) const {
	return allPieces[data[i][j]].color;
}

bool Board::placePieceAt(int i, int j, const Piece& piece) {
	for (int a = 0; a < piece.bitmask.size(); ++a) {
		for (int b = 0; b < piece.bitmask[0].size(); ++b) {
			if (piece.bitmask[a][b]) {
				int boardi = a + i, boardj = b + j;
				if (boardi >= BOARD_SIZE || boardj >= BOARD_SIZE || data[boardi][boardj]) {
					return false;
				}
			}
		}
	}

	for (int a = 0; a < piece.bitmask.size(); ++a) {
		for (int b = 0; b < piece.bitmask[0].size(); ++b) {
			if (piece.bitmask[a][b]) {
				data[a + i][b + j] = piece.id;
			}
		}
	}
	return true;
}

} // namespace game