#pragma once

#include <array>
#include <random>

#include "rend/drawable.hpp"
#include "rend/board_drawable.hpp"
#include "rend/piece_drawable.hpp"

namespace game {

class Game : rend::Drawable {
	static constexpr size_t PIECE_COUNT = 3;

	Board board;
	std::array<Piece::id_t, PIECE_COUNT> pieces;

	rend::BoardDrawable boardDrawable;
	std::array<rend::PieceDrawable, PIECE_COUNT> pieceDrawables;

	int movedPiece = PIECE_COUNT; // i.e. none
	float xGestureStart, yGestureStart;

	std::mt19937 randomNumberGenerator;
    std::uniform_int_distribution<std::mt19937::result_type> distribution;

	void resetPiecePositionsAndSizes();
	void generateNewPieces();

public:
	Game();

	void processEvent(const sf::Event& event);
	void draw(sf::RenderWindow& window) override;
};

} // namespace game
