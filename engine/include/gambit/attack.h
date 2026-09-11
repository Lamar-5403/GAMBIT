#pragma once
#include <gambit/board.h>
#include <array>
#include <utility>

namespace attacks {
    extern std::array<Bitboard, NUM_SQUARES> knight;
    extern std::array<Bitboard, NUM_SQUARES> king;
    extern std::array<Bitboard, NUM_SQUARES> whitePawn;
    extern std::array<Bitboard, NUM_SQUARES> blackPawn;

    void initializeKnightAttacks();
    void initializeKingAttacks();
    void initializeWhitePawnAttacks();
    void initializeBlackPawnAttacks();
}