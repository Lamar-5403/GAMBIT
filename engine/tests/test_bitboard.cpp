#include <gambit/board.h>
#include <iostream>
#include <bitset>

bool testBoard() {
    int failed = 0;

    for (int i = 0; i < NUM_SQUARES; i++) {
        Square square = static_cast<Square>(i);
        Bitboard board = squareToBitboard(square);
        std::cout << std::bitset<64>(board) << "\n";
        Bitboard expected = 1ULL << i;
        
        if (board != expected) {
            failed += 1;
            std::cout << "Square: " << squareToString(square) << " failed.\n";
        }
    }

    if (failed != 0) {
        return false;
    }
    
    std::cout << 64 - failed << "/64 passed.\n";
    return true;
}