#include "ai.hpp"

#include "raw/raw_board.hpp"
#include "raw/raw_piece.hpp"

namespace ai {

std::pair<float, std::vector<Move>> Ai::bruteForceWithScore(const raw_board_t& board, const std::vector<piece_id_t>& availablePieces) {
	if (availablePieces.empty()) {
		return {scoringFunction(board), {}};
	}

	const piece_id_t currentPieceId = availablePieces[0];
	const std::vector<piece_id_t> nextAvailablePieces{availablePieces.begin() + 1, availablePieces.end()};

	float bestScoreSoFar = 0.0f;
	std::vector<Move> bestMovesSoFar;
	for (int i = 0; i < app::BOARD_SIZE - raw::pieceHeight[currentPieceId] + 1; ++i) {
		for (int j = 0; j < app::BOARD_SIZE - raw::pieceWidth[currentPieceId] + 1; ++j) {
			if (raw::fitsPieceAt(board, i, j, currentPieceId)) {
				raw_board_t newBoard = board;
				raw::placePieceAt(newBoard, i, j, currentPieceId);

				auto [score, moves] = bruteForceWithScore(newBoard, nextAvailablePieces);
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

Ai::Ai(const ai::scoring_function_t& scoringFunction)
		: scoringFunction{scoringFunction} {}

std::vector<Move> Ai::bruteForce(const raw_board_t& board, std::vector<piece_id_t> availablePieces) {
	sort(availablePieces.begin(), availablePieces.end());

	float bestScoreSoFar = 0.0f;
	std::vector<Move> bestMovesSoFar;
	do {
		auto [score, moves] = bruteForceWithScore(board, availablePieces);
		if (score > bestScoreSoFar) {
			bestScoreSoFar = score;
			bestMovesSoFar = moves;
		}
	} while (std::next_permutation(availablePieces.begin(), availablePieces.end()));

	return {bestMovesSoFar.rbegin(), bestMovesSoFar.rend()}; // reverse vector to have ordered moves
}

std::vector<Move> Ai::bestCombinationOfSingleMoves(const raw_board_t& board, std::vector<piece_id_t> availablePieces) {
	sort(availablePieces.begin(), availablePieces.end());

	float bestScoreSoFar = 0.0f;
	std::vector<Move> bestMovesSoFar;
	do {
		float score = 0.0f;
		std::vector<Move> moves;
		raw_board_t currentBoard = board;
		for (auto availablePiece : availablePieces) {
			auto [partialScore, partialMoves] = bruteForceWithScore(currentBoard, {availablePiece});
			if (partialMoves.empty()) {
				break; // has lost
			}

			score += partialScore;
			moves.push_back(partialMoves[0]);
			raw::placePieceAt(currentBoard, partialMoves[0].i, partialMoves[0].j, availablePiece);
		}

		if (score > bestScoreSoFar) {
			bestScoreSoFar = score;
			bestMovesSoFar = moves;
		}
	} while (std::next_permutation(availablePieces.begin(), availablePieces.end()));

	return bestMovesSoFar;
}

} // namespace ai