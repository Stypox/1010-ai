#include "application.hpp"

#include <SFML/Graphics.hpp>
#include <string>

#include "app/config.hpp"
#include "app/constants.hpp"
#include "util/graphics.hpp"

namespace app {

sf::RenderWindow Application::window{};

void Application::drawUi() {
    sf::Text title = util::buildText(TITLE, TITLE_CHARACTER_SIZE);
    util::setOriginAtCenter(title);
    title.setPosition(LEFT_SECTION_WIDTH / 2, 20);
    window.draw(title);

    sf::RectangleShape rectangle;
    rectangle.setSize({RIGHT_SECTION_WIDTH, WINDOW_HEIGHT});
    rectangle.setPosition(LEFT_SECTION_WIDTH, 0);
    rectangle.setFillColor(RIGHT_BACKGROUND_COLOR);
    window.draw(rectangle);
}

void Application::run() {
    window.create(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        WINDOW_NAME,
        sf::Style::Titlebar | sf::Style::Close);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(LEFT_BACKGROUND_COLOR);
        drawUi();
        window.display();
    }
}

}
