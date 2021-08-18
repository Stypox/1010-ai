#pragma once

#include <cstdint>
#include <array>

#include "game/board.hpp"

namespace raw {

// all are 50 bits long
constexpr raw_board_t pieceMask[] {
	0b0, // pieceNone
	0b1000000000'1000000000'1000000000'1000000000'1000000000, // pieceLong5Vertical
	0b1000000000'1000000000'1000000000'1000000000'0000000000, // pieceLong4Vertical
	0b1000000000'1000000000'1000000000'0000000000'0000000000, // pieceLong3Vertical
	0b1000000000'1000000000'0000000000'0000000000'0000000000, // pieceLong2Vertical
	0b1111100000'0000000000'0000000000'0000000000'0000000000, // pieceLong5Horizontal
	0b1111000000'0000000000'0000000000'0000000000'0000000000, // pieceLong4Horizontal
	0b1110000000'0000000000'0000000000'0000000000'0000000000, // pieceLong3Horizontal
	0b1100000000'0000000000'0000000000'0000000000'0000000000, // pieceLong2Horizontal
	0b1110000000'1110000000'1110000000'0000000000'0000000000, // pieceSquare3x3
	0b1100000000'1100000000'0000000000'0000000000'0000000000, // pieceSquare2x2
	0b1110000000'1000000000'1000000000'0000000000'0000000000, // pieceAngle3x3TL
	0b1110000000'0010000000'0010000000'0000000000'0000000000, // pieceAngle3x3TR
	0b0010000000'0010000000'1110000000'0000000000'0000000000, // pieceAngle3x3BR
	0b1000000000'1000000000'1110000000'0000000000'0000000000, // pieceAngle3x3BL
	0b1100000000'1000000000'0000000000'0000000000'0000000000, // pieceAngle2x2TL
	0b1100000000'0100000000'0000000000'0000000000'0000000000, // pieceAngle2x2TR
	0b0100000000'1100000000'0000000000'0000000000'0000000000, // pieceAngle2x2BR
	0b1000000000'1100000000'0000000000'0000000000'0000000000, // pieceAngle2x2BL
	0b1000000000'0000000000'0000000000'0000000000'0000000000, // pieceSingle
};

constexpr board_index_t pieceWidth[] {
	0, // pieceNone
	1, // pieceLong5Vertical
	1, // pieceLong4Vertical
	1, // pieceLong3Vertical
	1, // pieceLong2Vertical
	5, // pieceLong5Horizontal
	4, // pieceLong4Horizontal
	3, // pieceLong3Horizontal
	2, // pieceLong2Horizontal
	3, // pieceSquare3x3
	2, // pieceSquare2x2
	3, // pieceAngle3x3TL
	3, // pieceAngle3x3TR
	3, // pieceAngle3x3BR
	3, // pieceAngle3x3BL
	2, // pieceAngle2x2TL
	2, // pieceAngle2x2TR
	2, // pieceAngle2x2BR
	2, // pieceAngle2x2BL
	1, // pieceSingle
};

constexpr board_index_t pieceHeight[] {
	0, // pieceNone
	5, // pieceLong5Vertical
	4, // pieceLong4Vertical
	3, // pieceLong3Vertical
	2, // pieceLong2Vertical
	1, // pieceLong5Horizontal
	1, // pieceLong4Horizontal
	1, // pieceLong3Horizontal
	1, // pieceLong2Horizontal
	3, // pieceSquare3x3
	2, // pieceSquare2x2
	3, // pieceAngle3x3TL
	3, // pieceAngle3x3TR
	3, // pieceAngle3x3BR
	3, // pieceAngle3x3BL
	2, // pieceAngle2x2TL
	2, // pieceAngle2x2TR
	2, // pieceAngle2x2BR
	2, // pieceAngle2x2BL
	1, // pieceSingle
};

// the points given by each piece are just the number of squares
constexpr int piecePoints[] {
	0, // pieceNone
	5, // pieceLong5Vertical
	4, // pieceLong4Vertical
	3, // pieceLong3Vertical
	2, // pieceLong2Vertical
	5, // pieceLong5Horizontal
	4, // pieceLong4Horizontal
	3, // pieceLong3Horizontal
	2, // pieceLong2Horizontal
	9, // pieceSquare3x3
	4, // pieceSquare2x2
	5, // pieceAngle3x3TL
	5, // pieceAngle3x3TR
	5, // pieceAngle3x3BR
	5, // pieceAngle3x3BL
	3, // pieceAngle2x2TL
	3, // pieceAngle2x2TR
	3, // pieceAngle2x2BR
	3, // pieceAngle2x2BL
	1, // pieceSingle
};

} // namespace raw