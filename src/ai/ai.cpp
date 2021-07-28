#include "ai.hpp"

namespace ai {

float calculateScore(const game::Board& board) {
	float score = 0.0f;
	for (const auto& [id, partialScore] : scoringTable) {
		const game::Piece& piece = game::allPieces[id];
		for (int i = 0; i < app::BOARD_SIZE; ++i) {
			for (int j = 0; j < app::BOARD_SIZE; ++j) {
				if (board.fitsPieceAt(i, j, piece)) {
					score += partialScore;
				}
			}
		}
	}
	return score;
}

std::pair<float, std::vector<Move>> getBestMovesWithScore(const game::Board& board, const std::vector<game::Piece::id_t>& availablePieces) {
	if (availablePieces.empty()) {
		return {calculateScore(board), {}};
	}

	const game::Piece::id_t currentPieceId = availablePieces[0];
	const game::Piece& currentPiece = game::allPieces[currentPieceId];
	const std::vector<game::Piece::id_t> nextAvailablePieces{availablePieces.begin() + 1, availablePieces.end()};

	float bestScoreSoFar = 0.0f;
	std::vector<Move> bestMovesSoFar;
	for (int i = 0; i < app::BOARD_SIZE; ++i) {
		for (int j = 0; j < app::BOARD_SIZE; ++j) {
			if (board.fitsPieceAt(i, j, currentPiece)) {
				game::Board newBoard = board;
				newBoard.placePieceAt(i, j, currentPiece);

				auto [score, moves] = getBestMovesWithScore(newBoard, nextAvailablePieces);
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

std::vector<Move> bruteForce(const game::Board& board, std::vector<game::Piece::id_t> availablePieces) {
	sort(availablePieces.begin(), availablePieces.end());

	float bestScoreSoFar = 0.0f;
	std::vector<Move> bestMovesSoFar;
	do {
		auto [score, moves] = getBestMovesWithScore(board, availablePieces);
		if (score > bestScoreSoFar) {
			bestScoreSoFar = score;
			bestMovesSoFar = moves;
		}
	} while (std::next_permutation(availablePieces.begin(), availablePieces.end()));

	return {bestMovesSoFar.rbegin(), bestMovesSoFar.rend()}; // reverse vector to have ordered moves
}

std::vector<Move> bestCombinationOfSingleMoves(const game::Board& board, std::vector<game::Piece::id_t> availablePieces) {
	sort(availablePieces.begin(), availablePieces.end());

	float bestScoreSoFar = 0.0f;
	std::vector<Move> bestMovesSoFar;
	do {
		float score = 0.0f;
		std::vector<Move> moves;
		game::Board currentBoard = board;
		for (auto availablePiece : availablePieces) {
			auto [partialScore, partialMoves] = getBestMovesWithScore(currentBoard, {availablePiece});
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