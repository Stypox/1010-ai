#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "rend/drawable.hpp"
#include "game/piece.hpp"

namespace rend {

class PieceDrawable : Drawable {
	float xPrev = 0.0f;
	float yPrev = 0.0f;
	std::vector<sf::RectangleShape> rectangles;

public:
	void updatePiece(const game::Piece& piece);
	void setCenterPosition(const float x, const float y);
	void draw(sf::RenderWindow& window) override;
};

} // namespace rend