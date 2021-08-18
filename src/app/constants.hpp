#pragma once

#include <cstdint>
#include <string>
#include <SFML/Graphics.hpp>

#include "app/config.hpp"
#include "util/typedefs.hpp"

namespace app {

constexpr board_index_t BOARD_SIZE = 10; // 10x10 squares

const std::string WINDOW_NAME = std::string(PROJECT_NAME) + " " + std::to_string(VERSION_MAJOR) + "." + std::to_string(VERSION_MINOR);
constexpr unsigned int WINDOW_WIDTH = 900;
constexpr unsigned int WINDOW_HEIGHT = 600;
constexpr unsigned int LEFT_SECTION_WIDTH = 300;
constexpr unsigned int RIGHT_SECTION_WIDTH = WINDOW_WIDTH - LEFT_SECTION_WIDTH;
constexpr unsigned int LEFT_SECTION_TITLE_HEIGHT = 78;
constexpr unsigned int LEFT_SECTION_PIECE_HEIGHT = 168;

constexpr unsigned int SQUARE_SIZE = 40;
constexpr unsigned int SQUARE_PADDING = 5;
constexpr unsigned int PIECE_COUNT = 3;

constexpr const char* STRING_TITLE = "Welcome to 1010";
constexpr const char* STRING_POINTS = "%d points";
constexpr const char* STRING_YOU_LOST = "You lost! You scored %d points";
constexpr const char* STRING_PLAY_AGAIN = "Press SPACE to play again";

constexpr float LETTER_SPACING = 1.5f;
constexpr unsigned int HEADER_CHARACTER_SIZE = 20;
constexpr unsigned int SUBHEADER_CHARACTER_SIZE = 17;

const sf::Color LEFT_BACKGROUND_COLOR = sf::Color{30, 30, 30};
const sf::Color RIGHT_BACKGROUND_COLOR = sf::Color{20, 20, 20};
const sf::Color TEXT_COLOR = sf::Color::White;

const sf::Color COLOR_PIECE_NONE = sf::Color{60, 60, 60};
const sf::Color COLOR_PIECE_LONG5 = sf::Color{209, 106, 91};
const sf::Color COLOR_PIECE_LONG4 = sf::Color{232, 107, 121};
const sf::Color COLOR_PIECE_LONG3 = sf::Color{236, 149, 80};
const sf::Color COLOR_PIECE_LONG2 = sf::Color{255, 198, 57};
const sf::Color COLOR_PIECE_SQUARE_3X3 = sf::Color{58, 219, 175};
const sf::Color COLOR_PIECE_SQUARE_2X2 = sf::Color{148, 220, 94};
const sf::Color COLOR_PIECE_ANGLE_3X3 = sf::Color{87, 191, 230};
const sf::Color COLOR_PIECE_ANGLE_2X2 = sf::Color{89, 203, 133};
const sf::Color COLOR_PIECE_SINGLE = sf::Color{120, 143, 221};

} // namespace app