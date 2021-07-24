#include "piece_drawable.hpp"

#include "app/constants.hpp"

namespace rend {

void PieceDrawable::updatePiece(const game::Piece& piece) {
	if (piece.bitmask.empty()) {
		rectangles.resize(0);
		return;
	}

	float squareSpacing = zoomPrev * (app::SQUARE_SIZE + app::SQUARE_PADDING * 2);
	float xPiece = xPrev - piece.bitmask[0].size() * squareSpacing / 2.0f;
	float yPiece = yPrev - piece.bitmask.size() * squareSpacing / 2.0f;

	int rectanglesIndex = 0;
	for (int i = 0; i < piece.bitmask.size(); ++i) {
		for (int j = 0; j < piece.bitmask[0].size(); ++j) {
			if (piece.bitmask[i][j]) {
				if (rectanglesIndex >= rectangles.size()) {
					rectangles.push_back(sf::RectangleShape{
						{zoomPrev * app::SQUARE_SIZE, zoomPrev * app::SQUARE_SIZE}});
				}
				sf::RectangleShape& rectangle = rectangles[rectanglesIndex];
				rectangle.setPosition({xPiece + zoomPrev * app::SQUARE_PADDING + squareSpacing * j,
									   yPiece + zoomPrev * app::SQUARE_PADDING + squareSpacing * i});
				rectangle.setFillColor(piece.color);
				++rectanglesIndex;
			}
		}
	}

	rectangles.resize(rectanglesIndex);
}

void PieceDrawable::setCenterPositionAndZoom(const float x, const float y, const float zoom) {
	const sf::Vector2f toSum{x - xPrev, y - yPrev};
	for (auto&& rectangle : rectangles) {
		rectangle.setSize({zoom * app::SQUARE_SIZE, zoom * app::SQUARE_SIZE});
		rectangle.setPosition((rectangle.getPosition() - sf::Vector2f{xPrev, yPrev}) / zoomPrev * zoom + sf::Vector2f{x, y});
	}
	xPrev = x;
	yPrev = y;
	zoomPrev = zoom;
}

void PieceDrawable::draw(sf::RenderWindow& window) {
	for (auto&& rectangle : rectangles) {
		window.draw(rectangle);
	}
}

} // namespace rend