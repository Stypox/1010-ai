#pragma once

#include <SFML/Graphics.hpp>

#include "rend/drawable.hpp"
#include "game/game.hpp"
#include "app/constants.hpp"

namespace rend {

class Ui : Drawable {

	sf::Text titleText;
	sf::Text scoreText;

	sf::RectangleShape rightRectangle;
	sf::Text youLostText;
	sf::Text playAgainText;

	rend::BoardDrawable boardDrawable;
	std::array<rend::PieceDrawable, app::PIECE_COUNT> pieceDrawables;

	int movedPiece = app::PIECE_COUNT; // i.e. none
	float xGestureStart, yGestureStart;

	void updateScore(unsigned int score);
	void updateHasLost(bool hasLost, unsigned int score);

	void resetPiecePositionsAndSizes();

	void onMouseLeftPressed(game::Game& game, int x, int y);
	void onMouseMoved(int x, int y);
	void onMouseLeftReleased(game::Game& game, int x, int y);
	void onSpaceReleased(game::Game& game);

public:
	Ui();

	void processEvent(game::Game& game, const sf::Event& event);
	void updateGame(const game::Game& game);
	void draw(sf::RenderWindow& window) override;
};

} // namespace rend