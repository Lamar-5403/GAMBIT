#pragma once
#include <gambit/board.h>
#include <array>
#include <utility>

namespace attacks {
    extern std::array<Bitboard, NUM_SQUARES> whitePawnAttackTable;
    extern std::array<Bitboard, NUM_SQUARES> blackPawnAttackTable;
    extern std::array<Bitboard, NUM_SQUARES> knightAttackTable;
    extern std::array<Bitboard, NUM_SQUARES> kingAttackTable;

    void initializeWhitePawnAttackTable();
    void initializeBlackPawnAttackTable();
    void initializeKnightAttackTable();
    void initializeKingAttackTable();
}