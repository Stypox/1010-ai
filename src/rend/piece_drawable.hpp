#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "rend/drawable.hpp"
#include "game/piece.hpp"

namespace rend {

class PieceDrawable : Drawable {
	float xPrev = 0.0f;
	float yPrev = 0.0f;
	float zoomPrev = 1.0f;
	std::vector<sf::RectangleShape> rectangles;

public:
	std::pair<float, float> getUpperLeftVertexPosition();

	void updatePiece(const game::Piece& piece);
	void setCenterPositionAndZoom(const float x, const float y, const float zoom);
	void draw(sf::RenderWindow& window) override;
};

} // namespace rend