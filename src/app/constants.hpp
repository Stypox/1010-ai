#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "app/config.hpp"

namespace app {

const std::string WINDOW_NAME = std::string(PROJECT_NAME) + " " + std::to_string(VERSION_MAJOR) + "." + std::to_string(VERSION_MINOR);
constexpr unsigned int WINDOW_WIDTH = 900;
constexpr unsigned int WINDOW_HEIGHT = 600;
constexpr unsigned int LEFT_SECTION_WIDTH = 300;
constexpr unsigned int RIGHT_SECTION_WIDTH = WINDOW_WIDTH - LEFT_SECTION_WIDTH;

constexpr const char* STRING_TITLE = "Welcome to 1010";
constexpr const char* STRING_POINTS = "%d points";

constexpr float LETTER_SPACING = 1.5f;
constexpr unsigned int HEADER_CHARACTER_SIZE = 20;
constexpr unsigned int SUBHEADER_CHARACTER_SIZE = 17;

const sf::Color LEFT_BACKGROUND_COLOR = sf::Color{30, 30, 30};
const sf::Color RIGHT_BACKGROUND_COLOR = sf::Color{20, 20, 20};
const sf::Color TEXT_COLOR = sf::Color::White;

} // namespace app