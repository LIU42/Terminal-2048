cmake_minimum_required(VERSION 3.0.0)
project(Terminal-2048 VERSION 0.1.0)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(Terminal-2048 main.cpp terminal2048.cpp terminal2048.h config.h)
target_link_libraries(Terminal-2048 ${CURSES_LIBRARY})
