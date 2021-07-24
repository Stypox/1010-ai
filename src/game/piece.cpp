#include "piece.hpp"

#include "app/constants.hpp"

namespace game {

Piece::Piece(const id_t id, const sf::Color& color, const std::vector<std::vector<bool>>& bitmask)
	: id{id}, color{color}, bitmask{bitmask} {}


constexpr bool T = true, F = false;

const Piece pieceNone = Piece(0, app::COLOR_PIECE_NONE,
	{});

const Piece pieceLong5Vertical = Piece(1, app::COLOR_PIECE_LONG5,
	{{T},
	 {T},
	 {T},
	 {T},
	 {T}});

const Piece pieceLong4Vertical = Piece(2, app::COLOR_PIECE_LONG4,
	{{T},
	 {T},
	 {T},
	 {T}});

const Piece pieceLong3Vertical = Piece(3, app::COLOR_PIECE_LONG3,
	{{T},
	 {T},
	 {T}});

const Piece pieceLong2Vertical = Piece(4, app::COLOR_PIECE_LONG2,
	{{T},
	 {T}});

const Piece pieceLong5Horizontal = Piece(5, app::COLOR_PIECE_LONG5,
	{{T, T, T, T, T}});

const Piece pieceLong4Horizontal = Piece(6, app::COLOR_PIECE_LONG4,
	{{T, T, T, T}});

const Piece pieceLong3Horizontal = Piece(7, app::COLOR_PIECE_LONG3,
	{{T, T, T}});

const Piece pieceLong2Horizontal = Piece(8, app::COLOR_PIECE_LONG2,
	{{T, T}});

const Piece pieceSquare3x3 = Piece(9, app::COLOR_PIECE_SQUARE_3X3,
	{{T, T, T},
	 {T, T, T},
	 {T, T, T}});

const Piece pieceSquare2x2 = Piece(10, app::COLOR_PIECE_SQUARE_2X2,
	{{T, T},
	 {T, T}});

// TLBR = Top, Left, Bottom, Right

const Piece pieceAngle3x3TL = Piece(11, app::COLOR_PIECE_ANGLE_3X3,
	{{T, T, T},
	 {T, F, F},
	 {T, F, F}});

const Piece pieceAngle3x3TR = Piece(12, app::COLOR_PIECE_ANGLE_3X3,
	{{T, T, T},
	 {F, F, T},
	 {F, F, T}});

const Piece pieceAngle3x3BR = Piece(13, app::COLOR_PIECE_ANGLE_3X3,
	{{F, F, T},
	 {F, F, T},
	 {T, T, T}});

const Piece pieceAngle3x3BL = Piece(14, app::COLOR_PIECE_ANGLE_3X3,
	{{T, F, F},
	 {T, F, F},
	 {T, T, T}});

const Piece pieceAngle2x2TL = Piece(15, app::COLOR_PIECE_ANGLE_2X2,
	{{T, T},
	 {T, F}});

const Piece pieceAngle2x2TR = Piece(16, app::COLOR_PIECE_ANGLE_2X2,
	{{T, T},
	 {F, T}});

const Piece pieceAngle2x2BR = Piece(17, app::COLOR_PIECE_ANGLE_2X2,
	{{F, T},
	 {T, T}});

const Piece pieceAngle2x2BL = Piece(18, app::COLOR_PIECE_ANGLE_2X2,
	{{T, F},
	 {T, T}});

const Piece pieceSingle = Piece(19, app::COLOR_PIECE_SINGLE,
	{{T}});


const std::array<Piece, 20> allPieces{
	pieceNone,
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