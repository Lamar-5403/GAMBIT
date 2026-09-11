#include <gambit/attack.h>
#include <iostream>

bool testKnightAttackTable() {
    attacks::initializeKnightAttackTable();

    if (attacks::knightAttackTable[static_cast<int>(Square::A8)] != (squareToBitboard(Square::B6) | squareToBitboard(Square::C7))) {
        return false;
    }

    if (attacks::knightAttackTable[static_cast<int>(Square::D4)] != (squareToBitboard(Square::B3) | squareToBitboard(Square::B5) | squareToBitboard(Square::C2) | squareToBitboard(Square::C6) | squareToBitboard(Square::E2)
                                                        | squareToBitboard(Square::E6) | squareToBitboard(Square::F3) | squareToBitboard(Square::F5))) {
        return false;
    }

    if (attacks::knightAttackTable[static_cast<int>(Square::H1)] != (squareToBitboard(Square::F2) | squareToBitboard(Square::G3))) {
        return false;
    }

    return true;
}