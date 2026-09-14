#pragma once
#include <gambit/board.h>
#include <array>
#include <optional>
#include <bit>

namespace attacks {

    enum class RayDirection {
        NORTH,
        SOUTH,
        EAST,
        WEST,
        NORTH_EAST,
        NORTH_WEST,
        SOUTH_EAST,
        SOUTH_WEST
    };

    struct SlidingRays {
        Bitboard north;
        Bitboard south;
        Bitboard east;
        Bitboard west;
        Bitboard northEast;
        Bitboard northWest;
        Bitboard southEast;
        Bitboard southWest;

        bool operator==(const SlidingRays&) const = default;
    };

    extern std::array<Bitboard, NUM_SQUARES> whitePawnAttackTable;
    extern std::array<Bitboard, NUM_SQUARES> blackPawnAttackTable;
    extern std::array<Bitboard, NUM_SQUARES> knightAttackTable;
    extern std::array<Bitboard, NUM_SQUARES> kingAttackTable;
    extern std::array<SlidingRays, NUM_SQUARES> slidingRayTable;

    void initializeWhitePawnAttackTable();
    void initializeBlackPawnAttackTable();
    void initializeKnightAttackTable();
    void initializeKingAttackTable();
    void initializeSlidingRayTable();

    std::optional<Square> getFirstBlocker(Bitboard ray, Bitboard occupancy, RayDirection direction);
    Bitboard truncateRay(Bitboard ray, Square firstBlocker, attacks::RayDirection direction);
}