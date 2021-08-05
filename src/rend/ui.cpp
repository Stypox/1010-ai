#include "ui.hpp"

#include "util/graphics.hpp"
#include "util/string.hpp"
#include "app/constants.hpp"

namespace rend {

void Ui::updateScore(unsigned int score) {
	scoreText.setString(util::format(app::STRING_POINTS, score));
	util::setOriginAtCenter(scoreText);
    scoreText.setPosition(app::LEFT_SECTION_WIDTH / 2, 55);
}

void Ui::updateHasLost(bool hasLost, unsigned int score) {
	if (hasLost) {
		youLostText.setString(util::format(app::STRING_YOU_LOST, score));
		playAgainText.setString(app::STRING_PLAY_AGAIN);

		util::setOriginAtCenter(youLostText);
		util::setOriginAtCenter(playAgainText);

		constexpr float xText = app::WINDOW_WIDTH - app::RIGHT_SECTION_WIDTH / 2;
		constexpr float boardHeight = app::BOARD_SIZE * app::SQUARE_SIZE
			+ 2 * (app::BOARD_SIZE - 1) * app::SQUARE_PADDING;
		constexpr float textDistanceFromBorder = (app::WINDOW_HEIGHT - boardHeight) / 4.0f;
		youLostText.setPosition(xText, textDistanceFromBorder);
		playAgainText.setPosition(xText, app::WINDOW_HEIGHT - textDistanceFromBorder);

	} else {
		youLostText.setString("");
		playAgainText.setString("");
	}
}


void Ui::resetPiecePositionsAndSizes() {
    for (int i = 0; i < app::PIECE_COUNT; ++i) {
        pieceDrawables[i].setCenterPositionAndZoom(
            app::LEFT_SECTION_WIDTH / 2,
            app::LEFT_SECTION_TITLE_HEIGHT + app::LEFT_SECTION_PIECE_HEIGHT * (0.5f + i),
            0.5f);
    }
}


void Ui::onMouseLeftPressed(game::Game& game, int x, int y) {
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

        if (game.getPieces()[movedPiece] == game::pieceNone.id) {
            // prevent moving pieces that have already been used
            movedPiece = app::PIECE_COUNT; // i.e. none
        }
    }
}

void Ui::onMouseMoved(int x, int y) {
    if (movedPiece < app::PIECE_COUNT) { // i.e. if a piece is being moved
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

void Ui::onMouseLeftReleased(game::Game& game, int x, int y) {
    if (movedPiece < app::PIECE_COUNT) { // i.e. if a piece is being moved
        onMouseMoved(x, y); // make sure the piece's position is correct

        auto [xPiece, yPiece] = pieceDrawables[movedPiece].getUpperLeftVertexPosition();
        constexpr float halfSquareOffset = app::SQUARE_SIZE / 2.0f + app::SQUARE_PADDING;
        auto [i, j, successful] = boardDrawable.getSquareAtPixel(xPiece + halfSquareOffset, yPiece + halfSquareOffset);

        if (successful) {
			game.placePieceReleasedAt(movedPiece, i, j);
		}

        movedPiece = app::PIECE_COUNT; // i.e. none
        resetPiecePositionsAndSizes();
    }
}

void Ui::onSpaceReleased(game::Game& game) {
    if (game.getHasLost()) {
        game.reset();
    }
}


Ui::Ui() :
		titleText{util::buildText(app::HEADER_CHARACTER_SIZE)},
		scoreText{util::buildText(app::SUBHEADER_CHARACTER_SIZE)},
		youLostText{util::buildText(app::HEADER_CHARACTER_SIZE)},
		playAgainText{util::buildText(app::HEADER_CHARACTER_SIZE)} {
	titleText.setString(app::STRING_TITLE);
	util::setOriginAtCenter(titleText);
    titleText.setPosition(app::LEFT_SECTION_WIDTH / 2, 30);

	updateScore(0);

	rightRectangle.setSize({app::RIGHT_SECTION_WIDTH, app::WINDOW_HEIGHT});
    rightRectangle.setPosition(app::LEFT_SECTION_WIDTH, 0);
    rightRectangle.setFillColor(app::RIGHT_BACKGROUND_COLOR);

	updateHasLost(false, 0);

	resetPiecePositionsAndSizes();
}


void Ui::processEvent(game::Game& game, const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        onMouseLeftPressed(game, event.mouseButton.x, event.mouseButton.y);
    } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        onMouseLeftReleased(game, event.mouseButton.x, event.mouseButton.y);
    } else if (event.type == sf::Event::MouseMoved) {
        onMouseMoved(event.mouseMove.x, event.mouseMove.y);
    } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
        onSpaceReleased(game);
    } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) {
        game.toggleUseAi();
    }
}

void Ui::updateGame(const game::Game& game) {
	updateScore(game.getScore());
	updateHasLost(game.getHasLost(), game.getScore());

	boardDrawable.updateBoard(game.getBoard());
	for (int i = 0; i < app::PIECE_COUNT; ++i) {
		pieceDrawables[i].updatePiece(game::allPieces[game.getPieces()[i]]);
	}
}

void Ui::draw(sf::RenderWindow& window) {
	window.draw(titleText);
	window.draw(scoreText);
	window.draw(rightRectangle);
	window.draw(youLostText);
	window.draw(playAgainText);

	boardDrawable.draw(window);
	for (int i = 0; i < app::PIECE_COUNT; ++i) {
		pieceDrawables[i].draw(window);
	}
}

} // namespace rend