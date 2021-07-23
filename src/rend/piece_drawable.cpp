#include "piece_drawable.hpp"

#include "app/constants.hpp"

namespace rend {

void PieceDrawable::updatePiece(const game::Piece& piece) {
	constexpr float rectangleSpacing = app::SQUARE_SIZE + app::SQUARE_PADDING * 2;
	float xPiece = xPrev - piece.bitmask[0].size() * rectangleSpacing / 2.0f;
	float yPiece = yPrev - piece.bitmask.size() * rectangleSpacing / 2.0f;

	int rectanglesIndex = 0;
	for (int i = 0; i < piece.bitmask.size(); ++i) {
		for (int j = 0; j < piece.bitmask[0].size(); ++j) {
			if (piece.bitmask[i][j]) {
				if (rectanglesIndex >= rectangles.size()) {
					rectangles.push_back(sf::RectangleShape{{app::SQUARE_SIZE, app::SQUARE_SIZE}});
				}
				sf::RectangleShape& rectangle = rectangles[rectanglesIndex];
				rectangle.setPosition({xPiece + app::SQUARE_PADDING + rectangleSpacing * j,
									   yPiece + app::SQUARE_PADDING + rectangleSpacing * i});
				rectangle.setFillColor(piece.color);
				++rectanglesIndex;
			}
		}
	}

	rectangles.resize(rectanglesIndex);
}

void PieceDrawable::setCenterPosition(const float x, const float y) {
	const sf::Vector2f toSum{x - xPrev, y - yPrev};
	for (auto&& rectangle : rectangles) {
		rectangle.setPosition(rectangle.getPosition() + toSum);
	}
	xPrev = x;
	yPrev = y;
}

void PieceDrawable::draw(sf::RenderWindow& window) {
	for (auto&& rectangle : rectangles) {
		window.draw(rectangle);
	}
}

} // namespace rend