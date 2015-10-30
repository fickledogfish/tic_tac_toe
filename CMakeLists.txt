# === Project Definition ===

cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(TicTacToe CXX)

set(CMAKE_CXX_STANDARD 11)

# === Configuration ===
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
configure_file(
    "${PROJECT_SOURCE_DIR}/src/config.hpp.in" # template
    "${PROJECT_BINARY_DIR}/conf/config.hpp"   # output
    )
include_directories("${PROJECT_BINARY_DIR}/conf")

# === Build Libraries ===

add_library(random src/random/random.cpp)
include_directories(src/random)

add_library(text src/text/text.cpp)
include_directories(src/text)

add_library(board src/board/Board.cpp)
include_directories(src/board)
target_link_libraries(board text random)

# === Build Executables ===
add_executable(main src/main)
target_link_libraries(
    main
    board text random
    )
