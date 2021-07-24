#include "game.hpp"

#include "app/constants.hpp"

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
        const Piece& piece = allPiecesEqualProbability[distribution(randomNumberGenerator)];
        pieces[i] = piece.id;
        pieceDrawables[i].updatePiece(piece);
    }
}

Game::Game()
        : randomNumberGenerator{std::random_device{}()},
        distribution{0, allPiecesEqualProbability.size() - 1} {
    generateNewPieces();
    resetPiecePositionsAndSizes();
}

void Game::processEvent(const sf::Event& event) {
    const bool isAPieceBeingMoved = movedPiece < PIECE_COUNT;
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (event.mouseButton.x < app::LEFT_SECTION_WIDTH && event.mouseButton.y > app::LEFT_SECTION_TITLE_HEIGHT) {
            if (event.mouseButton.y > app::LEFT_SECTION_TITLE_HEIGHT + 2 * app::LEFT_SECTION_PIECE_HEIGHT) {
                movedPiece = 2;
            } else if (event.mouseButton.y > app::LEFT_SECTION_TITLE_HEIGHT + app::LEFT_SECTION_PIECE_HEIGHT) {
                movedPiece = 1;
            } else {
                movedPiece = 0;
            }

            xGestureStart = event.mouseButton.x;
            yGestureStart = event.mouseButton.y;

            if (pieces[movedPiece] == pieceNone.id) {
                // prevent moving pieces that have already been used
                movedPiece = PIECE_COUNT; // i.e. none
            }
        }
    } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        if (isAPieceBeingMoved) {
            // remove piece that was used
            pieces[movedPiece] = pieceNone.id;
            pieceDrawables[movedPiece].updatePiece(pieceNone);
            movedPiece = PIECE_COUNT; // i.e. none
            resetPiecePositionsAndSizes();
        }
    } else if (event.type == sf::Event::MouseMoved) {
        if (isAPieceBeingMoved) {
            const float xOriginal = app::LEFT_SECTION_WIDTH / 2;
            const float yOriginal = app::LEFT_SECTION_TITLE_HEIGHT + app::LEFT_SECTION_PIECE_HEIGHT * (0.5f + movedPiece);

            const float x = xOriginal + event.mouseMove.x - xGestureStart;
            const float y = yOriginal + event.mouseMove.y - yGestureStart;

            float zoom;
            if (x < app::LEFT_SECTION_WIDTH / 2) {
                zoom = 0.5f;
            } else if (x < app::LEFT_SECTION_WIDTH) {
                zoom = 0.5f + (x - app::LEFT_SECTION_WIDTH / 2.0f) / app::LEFT_SECTION_WIDTH;
            } else {
                zoom = 1.0f;
            }

            pieceDrawables[movedPiece].setCenterPositionAndZoom(x, y, zoom);
        }
    }
}

void Game::draw(sf::RenderWindow& window) {
    boardDrawable.draw(window);
    pieceDrawables[0].draw(window);
    pieceDrawables[1].draw(window);
    pieceDrawables[2].draw(window);
}

} // namespace game