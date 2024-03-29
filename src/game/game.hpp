#pragma once

#include <array>
#include <random>

#include "rend/drawable.hpp"
#include "rend/board_drawable.hpp"
#include "rend/piece_drawable.hpp"
#include "ai/ai.hpp"

namespace game {

class Game {

	Board board;
	std::array<piece_id_t, app::PIECE_COUNT> pieces;
	int score = 0;
	bool hasLost = false;

	ai::Ai ai;
	bool useAi = false;

	std::mt19937 randomNumberGenerator;
    std::uniform_int_distribution<std::mt19937::result_type> distribution;


	void generateNewPieces();
	void generateNewPiecesIfNeeded();

	void calculateHasLost();

public:
	Game(const ai::Ai& ai);

	const Board& getBoard() const;
	const std::array<piece_id_t, app::PIECE_COUNT>& getPieces() const;
	int getScore() const;
	bool getHasLost() const;
	bool getUseAi() const;

	void toggleUseAi();
	void placePieceReleasedAt(int movedPiece, int i, int j);
	void reset();

	void tick();
};

} // namespace game
