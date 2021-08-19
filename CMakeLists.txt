cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME 1010_AI)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_BUILD_TYPE Debug)
set(ADDITIONAL_GCC_FLAGS "-O3")
#set(ADDITIONAL_GCC_FLAGS "-O0 -fsanitize=address -fsanitize=undefined")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${ADDITIONAL_GCC_FLAGS}")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${ADDITIONAL_GCC_FLAGS}")

project("${PROJECT_NAME}" VERSION 0.1)
configure_file(src/app/config.hpp.in src/app/config.hpp)

add_executable(
	"${PROJECT_NAME}"
	src/main.cpp
	src/app/application.cpp
	src/app/no_ui_application.cpp
	src/app/resources.cpp
	src/util/graphics.cpp
	src/util/string.cpp
	src/rend/ui.cpp
	src/rend/board_drawable.cpp
	src/rend/piece_drawable.cpp
	src/game/piece.cpp
	src/game/board.cpp
	src/game/game.cpp
	src/ai/ai.cpp
	src/ai/scoring_function.cpp
	src/raw/raw_board.cpp
)

target_include_directories("${PROJECT_NAME}" PUBLIC "${PROJECT_BINARY_DIR}" src/ lib/arg-parser/include/)
target_link_libraries("${PROJECT_NAME}" sfml-graphics sfml-window sfml-system)
