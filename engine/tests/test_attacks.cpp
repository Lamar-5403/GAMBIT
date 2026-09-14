#include <gambit/attack.h>
#include <gambit/position.h>
#include <iostream>
#include <vector>

bool testWhitePawnAttackTable() {
    attacks::initializeWhitePawnAttackTable();

    if (attacks::whitePawnAttackTable[static_cast<int>(Square::A8)] != 0) {
        return false;
    }

    if (attacks::whitePawnAttackTable[static_cast<int>(Square::A7)] != squareToBitboard(Square::B8)) {
        return false;
    }

    if (attacks::whitePawnAttackTable[static_cast<int>(Square::B7)] != (squareToBitboard(Square::A8) | squareToBitboard(Square::C8))) {
        return false;
    }

    if (attacks::whitePawnAttackTable[static_cast<int>(Square::E4)] != (squareToBitboard(Square::D5) | squareToBitboard(Square::F5))) {
        return false;
    }

    if (attacks::whitePawnAttackTable[static_cast<int>(Square::G2)] != (squareToBitboard(Square::F3) | squareToBitboard(Square::H3))) {
        return false;
    }

    if (attacks::whitePawnAttackTable[static_cast<int>(Square::H2)] != squareToBitboard(Square::G3)) {
        return false;
    }

    if (attacks::whitePawnAttackTable[static_cast<int>(Square::A1)] != 0) {
        return false;
    }

    std::cout << "PASS: White pawn attack table.\n";
    return true;
}

bool testBlackPawnAttackTable() {
    attacks::initializeBlackPawnAttackTable();
    
    if (attacks::blackPawnAttackTable[static_cast<int>(Square::A8)] != 0) {
        return false;
    }
    
    if (attacks::blackPawnAttackTable[static_cast<int>(Square::A7)] != squareToBitboard(Square::B6)) {
        return false;
    }
    
    if (attacks::blackPawnAttackTable[static_cast<int>(Square::B7)] != (squareToBitboard(Square::A6) | squareToBitboard(Square::C6))) {
        return false;
    }
    
    if (attacks::blackPawnAttackTable[static_cast<int>(Square::E4)] != (squareToBitboard(Square::D3) | squareToBitboard(Square::F3))) {
        return false;
    }
    
    if (attacks::blackPawnAttackTable[static_cast<int>(Square::G2)] != (squareToBitboard(Square::F1) | squareToBitboard(Square::H1))) {
        return false;
    }
    
    if (attacks::blackPawnAttackTable[static_cast<int>(Square::H2)] != squareToBitboard(Square::G1)) {
        return false;
    }
    
    if (attacks::blackPawnAttackTable[static_cast<int>(Square::A1)] != 0) {
        return false;
    }

    std::cout << "PASS: Black pawn attack table.\n";
    return true;
}

bool testKnightAttackTable() {
    attacks::initializeKnightAttackTable();
    
    if (attacks::knightAttackTable[static_cast<int>(Square::A8)] != 
    (squareToBitboard(Square::B6) | 
    squareToBitboard(Square::C7))) {
        return false;
    }
    
    if (attacks::knightAttackTable[static_cast<int>(Square::D4)] != 
    (squareToBitboard(Square::B3) | 
    squareToBitboard(Square::B5) | 
    squareToBitboard(Square::C2) | 
    squareToBitboard(Square::C6) | 
    squareToBitboard(Square::E2) | 
    squareToBitboard(Square::E6) | 
    squareToBitboard(Square::F3) | 
    squareToBitboard(Square::F5))) {
        return false;
    }
    
    if (attacks::knightAttackTable[static_cast<int>(Square::H1)] != 
    (squareToBitboard(Square::F2) | 
    squareToBitboard(Square::G3))) {
        return false;
    }
    
    std::cout << "PASS: Knight attack table.\n";
    return true;
}

bool testKingAttackTable() {
    attacks::initializeKingAttackTable();

    if (attacks::kingAttackTable[static_cast<int>(Square::A8)] !=
    (squareToBitboard(Square::B8) |
    squareToBitboard(Square::A7) |
    squareToBitboard(Square::B7))) {
        return false;
    }

    if (attacks::kingAttackTable[static_cast<int>(Square::D4)] !=
    (squareToBitboard(Square::C5) |
    squareToBitboard(Square::D5) |
    squareToBitboard(Square::E5) |
    squareToBitboard(Square::C4) |
    squareToBitboard(Square::E4) |
    squareToBitboard(Square::C3) |
    squareToBitboard(Square::D3) |
    squareToBitboard(Square::E3))) {
        return false;
    }

    if (attacks::kingAttackTable[static_cast<int>(Square::H3)] !=
    (squareToBitboard(Square::G4) |
    squareToBitboard(Square::H4) |
    squareToBitboard(Square::G3) |
    squareToBitboard(Square::G2) |
    squareToBitboard(Square::H2))) {
        return false;
    }

    std::cout << "PASS: King attack table.\n";
    return true;
}

bool testSlidingRayTable() {
    attacks::initializeSlidingRayTable();

    Bitboard expectedNorth = 0;
    Bitboard expectedSouth = 0;
    Bitboard expectedEast = 0;
    Bitboard expectedWest = 0;
    Bitboard expectedNorthEast = 0;
    Bitboard expectedNorthWest = 0;
    Bitboard expectedSouthEast = 0;
    Bitboard expectedSouthWest = 0;

    attacks::SlidingRays expectedE4rays = {
        expectedNorth | squareToBitboard(Square::E5)
        | squareToBitboard(Square::E6)
        | squareToBitboard(Square::E7)
        | squareToBitboard(Square::E8),
        expectedSouth | squareToBitboard(Square::E3)
        | squareToBitboard(Square::E2)
        | squareToBitboard(Square::E1),
        expectedEast | squareToBitboard(Square::F4)
        | squareToBitboard(Square::G4)
        | squareToBitboard(Square::H4),
        expectedWest | squareToBitboard(Square::D4)
        | squareToBitboard(Square::C4)
        | squareToBitboard(Square::B4)
        | squareToBitboard(Square::A4),
        expectedNorthEast | squareToBitboard(Square::F5)
        | squareToBitboard(Square::G6)
        | squareToBitboard(Square::H7),
        expectedNorthWest | squareToBitboard(Square::D5)
        | squareToBitboard(Square::C6)
        | squareToBitboard(Square::B7)
        | squareToBitboard(Square::A8),
        expectedSouthEast | squareToBitboard(Square::F3)
        | squareToBitboard(Square::G2)
        | squareToBitboard(Square::H1), 
        expectedSouthWest | squareToBitboard(Square::D3)
        | squareToBitboard(Square::C2)
        | squareToBitboard(Square::B1)
    };

    attacks::SlidingRays expectedA8rays = {
        expectedNorth,
        expectedSouth | squareToBitboard(Square::A7)
        | squareToBitboard(Square::A6)
        | squareToBitboard(Square::A5)
        | squareToBitboard(Square::A4)
        | squareToBitboard(Square::A3)
        | squareToBitboard(Square::A2)
        | squareToBitboard(Square::A1),
        expectedEast | squareToBitboard(Square::B8)
        | squareToBitboard(Square::C8)
        | squareToBitboard(Square::D8)
        | squareToBitboard(Square::E8)
        | squareToBitboard(Square::F8)
        | squareToBitboard(Square::G8)
        | squareToBitboard(Square::H8),
        expectedWest,
        expectedNorthEast,
        expectedNorthWest,
        expectedSouthEast | squareToBitboard(Square::B7)
        | squareToBitboard(Square::C6)
        | squareToBitboard(Square::D5)
        | squareToBitboard(Square::E4)
        | squareToBitboard(Square::F3)
        | squareToBitboard(Square::G2)
        | squareToBitboard(Square::H1), 
        expectedSouthWest
    };

    if (attacks::slidingRayTable[36] != expectedE4rays) {
        return false;
    }

    if (attacks::slidingRayTable[0] != expectedA8rays) {
        return false;
    }

    std::cout << "PASS: Sliding ray table initialization.\n";
    return true;
}

bool testGetFirstBlocker() {
    Position position = positionFromFEN("r7/4r3/8/5r2/3rQ3/8/6r1/1r6 w - - 0 1");
    Bitboard occupancy = position.getAllOccupancy();
    Bitboard ray = 0;
    Square source = Square::E4;
    const attacks::SlidingRays& rays = attacks::slidingRayTable[static_cast<int>(source)];
    std::vector<std::optional<Square>> expectedBlockers = {Square::E7, std::nullopt, std::nullopt, Square::D4, Square::F5, Square::A8, Square::G2, Square::B1};

    for (int i = 0; i < 8; i++) {
        switch (static_cast<attacks::RayDirection>(i)) {
            case attacks::RayDirection::NORTH:
                ray = rays.north;
            break;

            case attacks::RayDirection::SOUTH:
                ray = rays.south;
            break;

            case attacks::RayDirection::EAST:
                ray = rays.east;
            break;

            case attacks::RayDirection::WEST:
                ray = rays.west;
            break;

            case attacks::RayDirection::NORTH_EAST:
                ray = rays.northEast;
            break;

            case attacks::RayDirection::NORTH_WEST:
                ray = rays.northWest;
            break;

            case attacks::RayDirection::SOUTH_EAST:
                ray = rays.southEast;
            break;

            case attacks::RayDirection::SOUTH_WEST:
                ray = rays.southWest;
            break;
        }

        std::optional<Square> firstBlocker = attacks::getFirstBlocker(ray, occupancy, static_cast<attacks::RayDirection>(i));

        if (expectedBlockers[i] != firstBlocker) {
            return false;
        }
    }

    std::cout << "PASS: Get first blocker.\n";
    return true;
}