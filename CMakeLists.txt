cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME 1010_AI)

project("${PROJECT_NAME}" VERSION 0.1)
configure_file(src/ProjectConfig.h.in src/ProjectConfig.h)

add_executable("${PROJECT_NAME}" src/main.cpp)

target_include_directories("${PROJECT_NAME}" PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries("${PROJECT_NAME}" sfml-graphics sfml-window sfml-system)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
