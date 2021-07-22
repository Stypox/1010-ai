cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME 1010_AI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project("${PROJECT_NAME}" VERSION 0.1)
configure_file(src/app/config.hpp.in src/app/config.hpp)

add_executable(
	"${PROJECT_NAME}"
	src/main.cpp
	src/app/application.cpp
	src/app/resources.cpp
	src/util/graphics.cpp
	src/util/string.cpp
	src/rend/ui.cpp
)

target_include_directories("${PROJECT_NAME}" PUBLIC "${PROJECT_BINARY_DIR}" src/)
target_link_libraries("${PROJECT_NAME}" sfml-graphics sfml-window sfml-system)
