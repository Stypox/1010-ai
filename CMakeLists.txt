cmake_minimum_required(VERSION 3.10)

project(1010_AI VERSION 0.1)
configure_file(src/ProjectConfig.h.in src/ProjectConfig.h)

add_executable(1010_AI src/main.cpp)
target_include_directories(1010_AI PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(1010_AI sfml-graphics sfml-window sfml-system)