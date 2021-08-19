#pragma once

#include <vector>
#include <functional>

#include "ai/move.hpp"
#include "ai/scoring_function.hpp"
#include "game/board.hpp"
#include "raw/raw_board.hpp"
#include "raw/raw_piece.hpp"

namespace ai {

class Ai {
	const ai::scoring_function_t scoringFunction;

	inline std::pair<float, std::vector<Move>> bruteForceWithScore(const raw_board_t& board) {
		return {scoringFunction(board), {}};
	}

	template<typename... Ts>
	inline std::pair<float, std::vector<Move>> bruteForceWithScore(const raw_board_t& board, piece_id_t currentPieceId, Ts... nextAvailablePieces) {
		float bestScoreSoFar = 0.0f;
		std::vector<Move> bestMovesSoFar;
		for (int i = 0; i < app::BOARD_SIZE - raw::pieceHeight[currentPieceId] + 1; ++i) {
			for (int j = 0; j < app::BOARD_SIZE - raw::pieceWidth[currentPieceId] + 1; ++j) {
				if (raw::fitsPieceAtNoBoundaryChecks(board, i, j, currentPieceId)) {
					raw_board_t newBoard = board;
					raw::placePieceAt(newBoard, i, j, currentPieceId);

					auto [score, moves] = bruteForceWithScore(newBoard, nextAvailablePieces...);
					if (score > bestScoreSoFar) {
						bestScoreSoFar = score;
						bestMovesSoFar = std::move(moves);
						bestMovesSoFar.push_back({i, j, currentPieceId});
					}
				}
			}
		}

		return {bestScoreSoFar, bestMovesSoFar};
	}

public:
	Ai(const ai::scoring_function_t& scoringFunction);

	std::vector<Move> bruteForce(const raw_board_t& board, std::vector<piece_id_t> availablePieces);
	std::vector<Move> bestCombinationOfSingleMoves(const raw_board_t& board, std::vector<piece_id_t> availablePieces);
};

} // namespace ai