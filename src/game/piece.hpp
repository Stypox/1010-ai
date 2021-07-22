#pragma once

#include <vector>
#include <array>
#include <SFML/Graphics/Color.hpp>

namespace game {

struct Piece {
	const unsigned char id; // the index of this piece in the allPieces array
	const sf::Color color;
	const std::vector<std::vector<bool>> bitmask;

	Piece(const unsigned char id, const sf::Color& color, const std::vector<std::vector<bool>>& bitmask);
};

extern const Piece pieceLong5Vertical;
extern const Piece pieceLong4Vertical;
extern const Piece pieceLong3Vertical;
extern const Piece pieceLong2Vertical;
extern const Piece pieceLong5Horizontal;
extern const Piece pieceLong4Horizontal;
extern const Piece pieceLong3Horizontal;
extern const Piece pieceLong2Horizontal;
extern const Piece pieceSquare3x3;
extern const Piece pieceSquare2x2;
// TLBR = Top, Left, Bottom, Right
extern const Piece pieceAngle3x3TL;
extern const Piece pieceAngle3x3TR;
extern const Piece pieceAngle3x3BR;
extern const Piece pieceAngle3x3BL;
extern const Piece pieceAngle2x2TL;
extern const Piece pieceAngle2x2TR;
extern const Piece pieceAngle2x2BR;
extern const Piece pieceAngle2x2BL;
extern const Piece pieceSingle;

extern const std::array<Piece, 19> allPieces;
// pieces are repeated in order to obtain an array where each piece type
// (i.e. with the same color) occours the same times
extern const std::array<Piece, 36> allPiecesEqualProbability;

} // namespace game