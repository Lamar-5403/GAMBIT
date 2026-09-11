#include <gambit/attack.h>
#include <iostream>

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

    return true;
}