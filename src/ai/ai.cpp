#include "ai.hpp"

namespace ai {

std::pair<float, std::vector<Move>> Ai::bruteForceWithScore(const game::Board& board, const std::vector<game::Piece::id_t>& availablePieces) {
	if (availablePieces.empty()) {
		return {scoringFunction(board), {}};
	}

	const game::Piece::id_t currentPieceId = availablePieces[0];
	const game::Piece& currentPiece = game::allPieces[currentPieceId];
	const std::vector<game::Piece::id_t> nextAvailablePieces{availablePieces.begin() + 1, availablePieces.end()};

	float bestScoreSoFar = 0.0f;
	std::vector<Move> bestMovesSoFar;
	for (int i = 0; i < app::BOARD_SIZE - currentPiece.height + 1; ++i) {
		for (int j = 0; j < app::BOARD_SIZE - currentPiece.width + 1; ++j) {
			if (board.fitsPieceAt(i, j, currentPiece)) {
				game::Board newBoard = board;
				newBoard.placePieceAt(i, j, currentPiece);

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

Ai::Ai(const std::function<float(const game::Board&)>& scoringFunction)
		: scoringFunction{scoringFunction} {}

std::vector<Move> Ai::bruteForce(const game::Board& board, std::vector<game::Piece::id_t> availablePieces) {
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

std::vector<Move> Ai::bestCombinationOfSingleMoves(const game::Board& board, std::vector<game::Piece::id_t> availablePieces) {
	sort(availablePieces.begin(), availablePieces.end());

	float bestScoreSoFar = 0.0f;
	std::vector<Move> bestMovesSoFar;
	do {
		float score = 0.0f;
		std::vector<Move> moves;
		game::Board currentBoard = board;
		for (auto availablePiece : availablePieces) {
			auto [partialScore, partialMoves] = bruteForceWithScore(currentBoard, {availablePiece});
			if (partialMoves.empty()) {
				break; // has lost
			}

			score += partialScore;
			moves.push_back(partialMoves[0]);
			currentBoard.placePieceAt(partialMoves[0].i, partialMoves[0].j, game::allPieces[availablePiece]);
		}

		if (score > bestScoreSoFar) {
			bestScoreSoFar = score;
			bestMovesSoFar = moves;
		}
	} while (std::next_permutation(availablePieces.begin(), availablePieces.end()));

	return bestMovesSoFar;
}

} // namespace ai