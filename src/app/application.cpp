#include "application.hpp"

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "app/config.hpp"
#include "app/constants.hpp"
#include "util/graphics.hpp"

namespace app {

void Application::draw() {
    ui.updateGame(game);
    ui.draw(window);
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
            } else {
                ui.processEvent(game, event);
            }
        }

        window.clear(LEFT_BACKGROUND_COLOR);
        draw();
        window.display();

        game.tick();
        if (game.getUseAi() && game.getHasLost()) {
            std::cout << "Score: " << game.getScore() << "\n";
            game.reset();
        }
    }
}

}
