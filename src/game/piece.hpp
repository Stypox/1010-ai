#pragma once

#include <vector>
#include <array>
#include <SFML/Graphics/Color.hpp>

namespace game {

struct Piece {
	using id_t = uint8_t;

	const id_t id; // the index of this piece in the allPieces array
	const sf::Color color;
	const std::vector<std::vector<bool>> bitmask;
	const size_t height;
	const size_t width;

	Piece(const id_t id, const sf::Color& color, const std::vector<std::vector<bool>>& bitmask);
};

extern const Piece pieceNone;
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

// note: this array also contains pieceNone, which should never be
// presented to the user
extern const std::array<Piece, 20> allPieces;
// pieces are repeated in order to obtain an array where each piece type
// (i.e. with the same color) occours the same times
extern const std::array<Piece, 36> allPiecesEqualProbability;
// pieces are repeated in order to reflect the distribution in the original game
extern const std::array<Piece, 75> allPiecesGameProbability;

} // namespace game