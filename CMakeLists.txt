cmake_minimum_required(VERSION 3.20)

project(GAMBIT
        VERSION 0.1.0
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(gambit
    engine/src/main.cpp 
    engine/src/board.cpp 
    engine/src/position.cpp
    engine/tests/test_bitboard.cpp
    engine/tests/test_startingPosition.cpp
)

target_include_directories(gambit 
    PRIVATE 
        engine/include
)