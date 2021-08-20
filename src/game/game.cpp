#include "game.hpp"

#include <algorithm>
#include <vector>
#include <iostream>

#include "app/constants.hpp"
#include "ai/move.hpp"
#include "ai/ai.hpp"
#include "ai/scoring_function.hpp"
#include "raw/raw_board.hpp"

namespace game {

void Game::generateNewPieces() {
    for (int i = 0; i < app::PIECE_COUNT; ++i) {
        const Piece& piece = allPiecesGameProbability[distribution(randomNumberGenerator)];
        pieces[i] = piece.id;
    }
}

void Game::generateNewPiecesIfNeeded() {
    if (std::all_of(pieces.begin(), pieces.end(), [](piece_id_t id) { return id == pieceNone.id; })) {
        generateNewPieces();
    }
}


void Game::calculateHasLost() {
    hasLost = !std::any_of(pieces.begin(), pieces.end(), [this](piece_id_t id) {
        return id != pieceNone.id && board.fitsPieceAnywhere(id);
    });
}


Game::Game(const ai::Ai& ai)
        : ai{ai},
        randomNumberGenerator{std::random_device{}()},
        distribution{0, allPiecesGameProbability.size() - 1} {
    generateNewPieces();
}


const Board& Game::getBoard() const {
    return board;
}

const std::array<piece_id_t, app::PIECE_COUNT>& Game::getPieces() const {
    return pieces;
}

int Game::getScore() const {
    return score;
}

bool Game::getHasLost() const {
    return hasLost;
}

bool Game::getUseAi() const {
    return useAi;
}


void Game::toggleUseAi() {
    useAi = !useAi;
}

void Game::placePieceReleasedAt(int movedPiece, int i, int j) {
    if (board.fitsPieceAt(j, i, pieces[movedPiece])) {
        score += board.placePieceAt(j, i, pieces[movedPiece]);

        // remove piece that was used
        pieces[movedPiece] = pieceNone.id;

        generateNewPiecesIfNeeded();
        calculateHasLost();
    }
}

void Game::reset() {
    score = 0;
    board = Board();
    generateNewPieces();
    calculateHasLost();
}


void Game::tick() {
    if (useAi) {
        std::vector<piece_id_t> availablePieces;
        for (auto piece : pieces) {
            if (piece != pieceNone.id) {
                availablePieces.push_back(piece);
            }
        }

        auto moves = ai.bruteForce(board.getRawData(), availablePieces);
        for (auto move : moves) {
            if (!board.fitsPieceAt(move.i, move.j, move.id)) {
                std::cout << "The ai provided an invalid move: " << move.i << " " << move.j << " " << (int)move.id << "\n";
                useAi = false;
                return;
            }

            score += board.placePieceAt(move.i, move.j, move.id);

            int usedIndex = std::find(pieces.begin(), pieces.end(), move.id) - pieces.begin();
            pieces[usedIndex] = pieceNone.id;
        }
        if (moves.empty()) {
            std::cout << "The ai provided no moves\n";
            useAi = false;
            return;
        }

        generateNewPiecesIfNeeded();
        calculateHasLost();
    }
}

} // namespace game