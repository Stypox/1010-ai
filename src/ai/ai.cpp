#include "ai.hpp"

#include <pthread.h>
#include <cassert>

namespace ai {

struct BruteForceWithScoreArguments {
	const scoring_function_t& scoringFunction;
	raw_board_t board;
	std::vector<piece_id_t> pieces;
};

inline std::pair<float, std::vector<Move>> bruteForceWithScore(
		const scoring_function_t& scoringFunction,
		const raw_board_t& board) {
	return {scoringFunction(board), {}};
}

template<typename... Ts>
inline std::pair<float, std::vector<Move>> bruteForceWithScore(
		const scoring_function_t& scoringFunction,
		const raw_board_t& board,
		piece_id_t currentPieceId,
		Ts... nextAvailablePieces) {
	float bestScoreSoFar = 0.0f;
	std::vector<Move> bestMovesSoFar;
	for (int i = 0; i < app::BOARD_SIZE - raw::pieceHeight[currentPieceId] + 1; ++i) {
		for (int j = 0; j < app::BOARD_SIZE - raw::pieceWidth[currentPieceId] + 1; ++j) {
			if (raw::fitsPieceAtNoBoundaryChecks(board, i, j, currentPieceId)) {
				raw_board_t newBoard = board;
				raw::placePieceAt(newBoard, i, j, currentPieceId);

				auto [score, moves] = bruteForceWithScore(scoringFunction, newBoard, nextAvailablePieces...);
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

void* bruteForceWithScoreThread(void* voidArg) {
	BruteForceWithScoreArguments* arg = reinterpret_cast<BruteForceWithScoreArguments*>(voidArg);

	std::pair<float, std::vector<Move>> result;
	switch (arg->pieces.size()) {
	case 0:
		break;
	case 1:
		result = bruteForceWithScore(arg->scoringFunction, arg->board, arg->pieces[0]);
		break;
	case 2:
		result = bruteForceWithScore(arg->scoringFunction, arg->board, arg->pieces[0], arg->pieces[1]);
		break;
	case 3:
		result = bruteForceWithScore(arg->scoringFunction, arg->board, arg->pieces[0], arg->pieces[1], arg->pieces[2]);
		break;
	}

	delete arg;
	std::pair<float, std::vector<Move>>* resultPtr
		= new std::pair<float, std::vector<Move>>{result};
	return resultPtr;
}

Ai::Ai(const ai::scoring_function_t& scoringFunction)
		: scoringFunction{scoringFunction} {}

std::vector<Move> Ai::bruteForce(const raw_board_t& board, std::vector<piece_id_t> availablePieces) {
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	std::vector<pthread_t> threads;

	sort(availablePieces.begin(), availablePieces.end());
	do {
		pthread_t thread;
		pthread_create(&thread, &attr, bruteForceWithScoreThread,
			new BruteForceWithScoreArguments{scoringFunction, board, availablePieces});
		threads.push_back(thread);
	} while (std::next_permutation(availablePieces.begin(), availablePieces.end()));
	pthread_attr_destroy(&attr);


	float bestScoreSoFar = 0.0f;
	std::vector<Move> bestMovesSoFar;
	for (auto&& thread : threads) {
		void* voidResult;
		pthread_join(thread, &voidResult);
		std::pair<float, std::vector<Move>>* result = reinterpret_cast<std::pair<float, std::vector<Move>>*>(voidResult);

		if (result->first > bestScoreSoFar) {
			bestScoreSoFar = result->first;
			bestMovesSoFar = result->second;
		}
		delete result;
	}

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
			auto [partialScore, partialMoves] = bruteForceWithScore(scoringFunction, currentBoard, availablePiece);
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