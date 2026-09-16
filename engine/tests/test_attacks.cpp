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

bool testTruncateRay() {
    Bitboard northRay = attacks::slidingRayTable[static_cast<int>(Square::E4)].north;
    Bitboard southRay = attacks::slidingRayTable[static_cast<int>(Square::E4)].south;

    Square northBlocker = Square::E7;
    Square southBlocker = Square::E2;

    Bitboard expectedNorthRay = squareToBitboard(Square::E5) | squareToBitboard(Square::E6) | squareToBitboard(Square::E7);
    Bitboard expectedSouthRay = squareToBitboard(Square::E3) | squareToBitboard(Square::E2);

    if (attacks::truncateRay(northRay, northBlocker, attacks::RayDirection::NORTH) != expectedNorthRay) {
        return false;
    }

    if (attacks::truncateRay(southRay, southBlocker, attacks::RayDirection::SOUTH) != expectedSouthRay) {
        return false;
    }

    std::cout << "PASS: Ray truncation.\n";
    return true;
}

bool testIsSquareAttacked() {
    Position position = positionFromFEN("2kr1b1r/pppq1ppp/2n5/1B1pP3/5B2/P1PbPN1P/1P1N1PPn/R2QK2R w KQ - 0 1"); // sliding piece and knight both attack square
    bool passed = attacks::isSquareAttacked(position, Square::F1, Color::BLACK);

    if (!passed) {
        std::cout << "FAIL: Sliding piece and knight attack.\n";
    }

    position = positionFromFEN("2k2b1r/ppp2ppp/8/1B1qPn2/2b2Bn1/P1PrPN1P/1P1N1PP1/R2QK2R w KQ - 0 1"); // sliding piece blocked, flase
    passed &= !attacks::isSquareAttacked(position, Square::F1, Color::BLACK);

    if (!passed) {
        std::cout << "FAIL: Sliding piece blocked.\n";
    }

    position = positionFromFEN("2k2b1r/ppp2ppp/8/1B1qPn2/2br1Bn1/P1P1PN1P/1P1N1PP1/R2QK2R w KQ - 0 1"); // attacked by sliding piece
    passed &= attacks::isSquareAttacked(position, Square::F1, Color::BLACK);

    if (!passed) {
        std::cout << "FAIL: Sliding piece attack.\n";
    }
    
    position = positionFromFEN("2k2b1r/ppp2ppp/4N3/1B1qPn2/2br1Bn1/P1P1PN1P/1P3PP1/R2QK2R b KQ - 0 1"); // attacked by white knight
    passed &= attacks::isSquareAttacked(position, Square::C7, Color::WHITE);

    if (!passed) {
        std::cout << "FAIL: White knight attack.\n";
    }

    position = positionFromFEN("2k2b1r/ppp2ppp/4N3/1B1qPn2/2br1Bn1/P1P1PN1P/1P3PP1/R2QK2R b KQ - 0 1"); // square not attacked at all
    passed &= !attacks::isSquareAttacked(position, Square::A8, Color::WHITE);

    if (!passed) {
        std::cout << "FAIL: Unrelated square.\n";
    }
    
    position = positionFromFEN("2k2b1r/ppp2ppp/4N3/1B1qPn2/2br1Bn1/P1P1PN1P/1P3PP1/R2QK2R w KQ - 0 1"); // black king attack
    passed &= attacks::isSquareAttacked(position, Square::B8, Color::BLACK);

    if (!passed) {
        std::cout << "FAIL: Black king attack.\n";
    }

    position = positionFromFEN("2k2b1r/ppp2ppp/4N3/1B1qPn2/2br1Bn1/P1P1PN1P/1P3PP1/R2QK2R b KQ - 0 1"); // white pawn attack
    passed &= attacks::isSquareAttacked(position, Square::G4, Color::WHITE);

    if (!passed) {
        std::cout << "FAIL: White pawn attack.\n";
    }

    if (passed) {
        std::cout << "PASS: isSquareAttacked() logic.\n";
        return true;
    }

    return false;
}

bool testIsInCheck() {
    Position position = positionFromFEN("8/6k1/8/6Q1/8/8/1K6/8 b - - 0 1"); // Black in check
    bool passed = attacks::isInCheck(position, Color::BLACK);

    if (!passed) {
        std::cout << "FAIL: Black in check.\n";
    }
    
    position = positionFromFEN("8/6k1/8/3Q4/8/8/1K6/8 b - - 0 1"); // Black not in check
    passed &= !attacks::isInCheck(position, Color::BLACK);

    if (!passed) {
        std::cout << "FAIL: Black not in check.\n";
    }
    
    position = positionFromFEN("8/6k1/7p/8/2n5/8/1K6/8 w - - 0 1"); // White in check
    passed &= attacks::isInCheck(position, Color::WHITE);

    if (!passed) {
        std::cout << "FAIL: White in check.\n";
    }

    position = positionFromFEN("8/6k1/1r5p/8/8/1n6/1KP5/8 w - - 0 1"); // White not in check
    passed &= !attacks::isInCheck(position, Color::WHITE);

    if (!passed) {
        std::cout << "FAIL: White not in check.\n";
    }

    if (passed) {
        std::cout << "PASS: isInCheck() logic.\n";
        return true;
    }

    return false;
}