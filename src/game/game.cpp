#include "game.hpp"

#include <algorithm>
#include <vector>
#include <iostream>

#include "app/constants.hpp"
#include "ai/move.hpp"
#include "ai/ai.hpp"
#include "ai/scoring_function.hpp"

namespace game {

void Game::resetPiecePositionsAndSizes() {
    for (int i = 0; i < PIECE_COUNT; ++i) {
        pieceDrawables[i].setCenterPositionAndZoom(
            app::LEFT_SECTION_WIDTH / 2,
            app::LEFT_SECTION_TITLE_HEIGHT + app::LEFT_SECTION_PIECE_HEIGHT * (0.5f + i),
            0.5f);
    }
}

void Game::generateNewPieces() {
    for (int i = 0; i < PIECE_COUNT; ++i) {
        const Piece& piece = allPiecesGameProbability[distribution(randomNumberGenerator)];
        pieces[i] = piece.id;
        pieceDrawables[i].updatePiece(piece);
    }
}

void Game::generateNewPiecesIfNeeded() {
    if (std::all_of(pieces.begin(), pieces.end(), [](Piece::id_t id) { return id == pieceNone.id; })) {
        generateNewPieces();
    }
}

void Game::onMouseLeftPressed(int x, int y) {
    if (x < app::LEFT_SECTION_WIDTH && y > app::LEFT_SECTION_TITLE_HEIGHT) {
        if (y > app::LEFT_SECTION_TITLE_HEIGHT + 2 * app::LEFT_SECTION_PIECE_HEIGHT) {
            movedPiece = 2;
        } else if (y > app::LEFT_SECTION_TITLE_HEIGHT + app::LEFT_SECTION_PIECE_HEIGHT) {
            movedPiece = 1;
        } else {
            movedPiece = 0;
        }

        xGestureStart = x;
        yGestureStart = y;

        if (pieces[movedPiece] == pieceNone.id) {
            // prevent moving pieces that have already been used
            movedPiece = PIECE_COUNT; // i.e. none
        }
    }
}

void Game::onMouseMoved(int x, int y) {
    if (movedPiece < PIECE_COUNT) { // i.e. if a piece is being moved
        const float xOriginal = app::LEFT_SECTION_WIDTH / 2;
        const float yOriginal = app::LEFT_SECTION_TITLE_HEIGHT + app::LEFT_SECTION_PIECE_HEIGHT * (0.5f + movedPiece);

        const float xCenter = xOriginal + x - xGestureStart;
        const float yCenter = yOriginal + y - yGestureStart;

        float zoom;
        if (xCenter < app::LEFT_SECTION_WIDTH / 2) {
            zoom = 0.5f;
        } else if (xCenter < app::LEFT_SECTION_WIDTH) {
            zoom = 0.5f + (xCenter - app::LEFT_SECTION_WIDTH / 2.0f) / app::LEFT_SECTION_WIDTH;
        } else {
            zoom = 1.0f;
        }

        pieceDrawables[movedPiece].setCenterPositionAndZoom(xCenter, yCenter, zoom);
    }
}

void Game::onMouseLeftReleased(int x, int y) {
    if (movedPiece < PIECE_COUNT) { // i.e. if a piece is being moved
        onMouseMoved(x, y); // make sure the piece's position is correct

        auto [xPiece, yPiece] = pieceDrawables[movedPiece].getUpperLeftVertexPosition();
        constexpr float halfSquareOffset = app::SQUARE_SIZE / 2.0f + app::SQUARE_PADDING;
        auto [i, j, successful] = boardDrawable.getSquareAtPixel(xPiece + halfSquareOffset, yPiece + halfSquareOffset);

        if (successful && board.fitsPieceAt(j, i, allPieces[pieces[movedPiece]])) {
            score += board.placePieceAt(j, i, allPieces[pieces[movedPiece]]);
            boardDrawable.updateBoard(board);

            // remove piece that was used
            pieces[movedPiece] = pieceNone.id;
            pieceDrawables[movedPiece].updatePiece(pieceNone);
        }

        movedPiece = PIECE_COUNT; // i.e. none
        resetPiecePositionsAndSizes();
        generateNewPiecesIfNeeded();
    }
}

void Game::onSpaceReleased() {
    if (hasLost()) {
        reset();
    }
}

Game::Game()
        : score{0},
        randomNumberGenerator{std::random_device{}()},
        distribution{0, allPiecesGameProbability.size() - 1},
        ai{
            ai::FittingPiecesScoringFunction{ai::fastScoringTable}
            + ai::ConnectedComponentsScoringFunction{0.1f, 4}
        } {
    generateNewPieces();
    resetPiecePositionsAndSizes();
    boardDrawable.updateBoard(board);
}

int Game::getScore() const {
    return score;
}

bool Game::hasLost() const {
    for (int i = 0; i < PIECE_COUNT; ++i) {
        if (pieces[i] != pieceNone.id) {
            const Piece& piece = allPieces[pieces[i]];
            if (board.fitsPieceAnywhere(piece)) {
                return false;
            }
        }
    }
    return true;
}

void Game::reset() {
    score = 0;
    board = Board();
    boardDrawable.updateBoard(board);
    generateNewPieces();
}

void Game::processEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        onMouseLeftPressed(event.mouseButton.x, event.mouseButton.y);
    } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        onMouseLeftReleased(event.mouseButton.x, event.mouseButton.y);
    } else if (event.type == sf::Event::MouseMoved) {
        onMouseMoved(event.mouseMove.x, event.mouseMove.y);
    } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
        onSpaceReleased();
    } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) {
        useAi = !useAi;
    }
}

void Game::tick() {
    if (useAi) {
        if (hasLost()) {
            std::cout<<"Score: "<<score<<"\n";
            reset();
            return;
        }

        std::vector<Piece::id_t> availablePieces;
        for (auto piece : pieces) {
            if (piece != pieceNone.id) {
                availablePieces.push_back(piece);
            }
        }
        //availablePieces = {availablePieces[rand() % availablePieces.size()]};

        auto moves = ai.bestCombinationOfSingleMoves(board, availablePieces);
        for (auto move : moves) {
            if (!board.fitsPieceAt(move.i, move.j, allPieces[move.id])) {
                std::cout << "The ai provided an invalid move: " << move.i << " " << move.j << " " << (int)move.id << "\n";
                useAi = !useAi;
                break;
            }

            score += board.placePieceAt(move.i, move.j, allPieces[move.id]);
            boardDrawable.updateBoard(board);

            int usedIndex = std::find(pieces.begin(), pieces.end(), move.id) - pieces.begin();
            pieces[usedIndex] = pieceNone.id;
            pieceDrawables[usedIndex].updatePiece(pieceNone);
        }
        resetPiecePositionsAndSizes();
        generateNewPiecesIfNeeded();
    }
}

void Game::draw(sf::RenderWindow& window) {
    boardDrawable.draw(window);
    pieceDrawables[0].draw(window);
    pieceDrawables[1].draw(window);
    pieceDrawables[2].draw(window);
}

} // namespace game