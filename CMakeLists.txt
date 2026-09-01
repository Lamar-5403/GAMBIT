```cmake
cmake_minimum_required(VERSION 3.20)

project(GAMBIT
    VERSION 0.1.0
    LANGUAGES CXX
)

# Require C++20 across all development environments.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# GAMBIT engine
add_executable(gambit
    engine/src/main.cpp
    engine/src/board.cpp
    engine/src/position.cpp
    engine/src/move.cpp

    engine/tests/test_bitboard.cpp
    engine/tests/test_startingPosition.cpp
    engine/tests/test_move.cpp
)

# Project headers
target_include_directories(gambit
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/engine/include
)
```
