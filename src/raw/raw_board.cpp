#include "raw_board.hpp"

#include <iostream>

#include "raw/raw_piece.hpp"
#include "game/game.hpp"

namespace raw {

inline raw_board_t pieceMaskShifted(board_index_t i, board_index_t j, piece_id_t id) {
	int8_t shift = i * app::BOARD_SIZE + j - int8_t(50); // 50 is the number of bits in piece masks
	return (shift > 0) ? (pieceMask[id] >> shift) : (pieceMask[id] << -shift);
}

bool fitsPieceAt(const raw_board_t& board, board_index_t i, board_index_t j, piece_id_t id) {
	if (i + pieceHeight[id] > app::BOARD_SIZE || j + pieceWidth[id] > app::BOARD_SIZE) {
		return false;
	}

	return (board & pieceMaskShifted(i, j, id)) == 0;
}

bool fitsPieceAtNoBoundaryChecks(const raw_board_t& board, board_index_t i, board_index_t j, piece_id_t id) {
	return (board & pieceMaskShifted(i, j, id)) == 0;
}

constexpr raw_board_t verticalLineMask
	= (((raw_board_t) 0b1000000000'1000000000'1000000000'1000000000'1000000000) << 50)
	+ 0b1000000000'1000000000'1000000000'1000000000'1000000000;
constexpr raw_board_t horizontalLineMask = 0b1111111111;

int placePieceAt(raw_board_t& board, board_index_t i, board_index_t j, piece_id_t id) {
	board |= pieceMaskShifted(i, j, id);
	int points = piecePoints[id];

	uint16_t verticalLinesToClear = 0, horizontalLinesToClear = 0;
	board_index_t verticalLineCount = 0, horizontalLineCount = 0;
	for (board_index_t rowCol = 0; rowCol < app::BOARD_SIZE; ++rowCol) {
		raw_board_t shiftedVerticalLineMask = verticalLineMask >> rowCol;
		raw_board_t shiftedHorizontalLineMask = horizontalLineMask << ((board_index_t(9) - rowCol) * board_index_t(10));

		if ((board & shiftedVerticalLineMask) == shiftedVerticalLineMask) {
			verticalLinesToClear |= (uint16_t(1) << rowCol);
			++verticalLineCount;
		}
		if ((board & shiftedHorizontalLineMask) == shiftedHorizontalLineMask) {
			horizontalLinesToClear |= (uint16_t(1) << rowCol);
			++horizontalLineCount;
		}
	}

	points += (verticalLineCount + horizontalLineCount) * app::BOARD_SIZE
		- verticalLineCount * horizontalLineCount; // prevent duplicate removed squares
	for (board_index_t rowCol = 0; rowCol < app::BOARD_SIZE; ++rowCol) {
		if (verticalLinesToClear & (uint16_t(1) << rowCol)) {
			board &= ~(verticalLineMask >> rowCol);
		}
		if (horizontalLinesToClear & (uint16_t(1) << rowCol)) {
			board &= ~(horizontalLineMask << ((board_index_t(9) - rowCol) * board_index_t(10)));
		}
	}

	return points;
}


bool usedAt(const raw_board_t& board, board_index_t i, board_index_t j) {
	return board & (raw_board_t(1) << ((board_index_t(9) - i) * app::BOARD_SIZE + (board_index_t(9) - j)));
}

void printBoard(const raw_board_t& board) {
	for (int i = 0; i < app::BOARD_SIZE; ++i) {
		for (int j = 0; j < app::BOARD_SIZE; ++j) {
			std::cout << (usedAt(board, i, j) ? "#" : ".");
		}
		std::cout << std::endl;
	}
	std::cout << "----------" << std::endl;
}

} // namespace raw