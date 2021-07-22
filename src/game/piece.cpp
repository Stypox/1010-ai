#include "piece.hpp"

namespace game {

Piece::Piece(const id_t id, const sf::Color& color, const std::vector<std::vector<bool>>& bitmask)
	: id{id}, color{color}, bitmask{bitmask} {}


constexpr bool T = true, F = false;

const Piece pieceLong5Vertical = Piece(0, {209, 106, 91},
	{{T},
	 {T},
	 {T},
	 {T},
	 {T}});

const Piece pieceLong4Vertical = Piece(1, {232, 107, 121},
	{{T},
	 {T},
	 {T},
	 {T}});

const Piece pieceLong3Vertical = Piece(2, {236, 149, 80},
	{{T},
	 {T},
	 {T}});

const Piece pieceLong2Vertical = Piece(3, {255, 198, 57},
	{{T},
	 {T}});

const Piece pieceLong5Horizontal = Piece(4, {209, 106, 91},
	{{T, T, T, T, T}});

const Piece pieceLong4Horizontal = Piece(5, {232, 107, 121},
	{{T, T, T, T}});

const Piece pieceLong3Horizontal = Piece(6, {236, 149, 80},
	{{T, T, T}});

const Piece pieceLong2Horizontal = Piece(7, {255, 198, 57},
	{{T, T}});

const Piece pieceSquare3x3 = Piece(8, {58, 219, 175},
	{{T, T, T},
	 {T, T, T},
	 {T, T, T}});

const Piece pieceSquare2x2 = Piece(9, {148, 220, 94},
	{{T, T},
	 {T, T}});

// TLBR = Top, Left, Bottom, Right

const Piece pieceAngle3x3TL = Piece(10, {87, 191, 230},
	{{T, T, T},
	 {T, F, F},
	 {T, F, F}});

const Piece pieceAngle3x3TR = Piece(11, {87, 191, 230},
	{{T, T, T},
	 {F, F, T},
	 {F, F, T}});

const Piece pieceAngle3x3BR = Piece(12, {87, 191, 230},
	{{F, F, T},
	 {F, F, T},
	 {T, T, T}});

const Piece pieceAngle3x3BL = Piece(13, {87, 191, 230},
	{{T, F, F},
	 {T, F, F},
	 {T, T, T}});

const Piece pieceAngle2x2TL = Piece(14, {89, 203, 133},
	{{T, T},
	 {T, F}});

const Piece pieceAngle2x2TR = Piece(15, {89, 203, 133},
	{{T, T},
	 {F, T}});

const Piece pieceAngle2x2BR = Piece(16, {89, 203, 133},
	{{F, T},
	 {T, T}});

const Piece pieceAngle2x2BL = Piece(17, {89, 203, 133},
	{{T, F},
	 {T, T}});

const Piece pieceSingle = Piece(18, {120, 143, 221},
	{{T}});


const std::array<Piece, 19> allPieces{
	pieceLong5Vertical,
	pieceLong4Vertical,
	pieceLong3Vertical,
	pieceLong2Vertical,
	pieceLong5Horizontal,
	pieceLong4Horizontal,
	pieceLong3Horizontal,
	pieceLong2Horizontal,
	pieceSquare3x3,
	pieceSquare2x2,
	pieceAngle3x3TL,
	pieceAngle3x3TR,
	pieceAngle3x3BR,
	pieceAngle3x3BL,
	pieceAngle2x2TL,
	pieceAngle2x2TR,
	pieceAngle2x2BR,
	pieceAngle2x2BL,
	pieceSingle,
};

const std::array<Piece, 36> allPiecesEqualProbability{
	pieceLong5Vertical,
	pieceLong5Vertical,
	pieceLong4Vertical,
	pieceLong4Vertical,
	pieceLong3Vertical,
	pieceLong3Vertical,
	pieceLong2Vertical,
	pieceLong2Vertical,
	pieceLong5Horizontal,
	pieceLong5Horizontal,
	pieceLong4Horizontal,
	pieceLong4Horizontal,
	pieceLong3Horizontal,
	pieceLong3Horizontal,
	pieceLong2Horizontal,
	pieceLong2Horizontal,
	pieceSquare3x3,
	pieceSquare3x3,
	pieceSquare3x3,
	pieceSquare3x3,
	pieceSquare2x2,
	pieceSquare2x2,
	pieceSquare2x2,
	pieceSquare2x2,
	pieceAngle3x3TL,
	pieceAngle3x3TR,
	pieceAngle3x3BR,
	pieceAngle3x3BL,
	pieceAngle2x2TL,
	pieceAngle2x2TR,
	pieceAngle2x2BR,
	pieceAngle2x2BL,
	pieceSingle,
	pieceSingle,
	pieceSingle,
	pieceSingle,
};

} // namespace game