#include "ai.hpp"

namespace ai {

Ai::Ai(const ai::scoring_function_t& scoringFunction)
		: scoringFunction{scoringFunction} {}

std::vector<Move> Ai::bruteForce(const raw_board_t& board, std::vector<piece_id_t> availablePieces) {
	sort(availablePieces.begin(), availablePieces.end());

	float bestScoreSoFar = 0.0f;
	std::vector<Move> bestMovesSoFar;
	do {
		std::pair<float, std::vector<Move>> result;
		switch (availablePieces.size()) {
		case 0:
			break;
		case 1:
			result = bruteForceWithScore(board, availablePieces[0]);
			break;
		case 2:
			result = bruteForceWithScore(board, availablePieces[0], availablePieces[1]);
			break;
		case 3:
			result = bruteForceWithScore(board, availablePieces[0], availablePieces[1], availablePieces[2]);
			break;
		}
		if (result.first > bestScoreSoFar) {
			bestScoreSoFar = result.first;
			bestMovesSoFar = result.second;
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
			auto [partialScore, partialMoves] = bruteForceWithScore(currentBoard, availablePiece);
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