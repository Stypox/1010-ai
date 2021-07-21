#include "application.hpp"

#include <SFML/Graphics.hpp>
#include <string>

#include "config.hpp"

namespace app {

sf::RenderWindow Application::window{};

void Application::drawUi() {
    sf::Text title;
    //title.setFont(sf::Font::loadFromFile("./res/SatellaRegular-ZVVaz.ttf"));
    title.setString("Welcome to 1010");
    title.setCharacterSize(20);
    title.setFillColor(textColor);
    window.draw(title);
}

void Application::run() {
    window.create(
        sf::VideoMode(800, 600),
        std::string(PROJECT_NAME) + " " + std::to_string(VERSION_MAJOR) + "." + std::to_string(VERSION_MINOR),
        sf::Style::Titlebar | sf::Style::Close);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(backgroundColor);
        drawUi();
        window.display();
    }
}

}
