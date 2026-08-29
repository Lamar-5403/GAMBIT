#include <gambit/board.h>
#include <iostream>
#include <bitset>

bool testBoard() {
    int failed = 0;

    for (int i = 0; i < NUM_SQUARES; i++) {
        Square square = static_cast<Square>(i);
        std::cout << "Testing square: " << squareToFile(square) << squareToRank(square) << "\n";
        Bitboard board = squareToBitboard(square);
        std::cout << std::bitset<64>(board) << "\n";
        Bitboard expected = 1ULL << i;
        
        if (board != expected) {
            failed += 1;
            std::cout << "Square: " << squareToFile(square) << squareToRank(square) << " failed.\n";
        }
    }

    if (failed != 0) {
        return false;
    }
    
    std::cout << NUM_SQUARES - failed << "/64 passed.\n";
    return true;
}

bool testRank() {
    int failed = 0;

    if (squareToRank(Square::A1) != 1) {
        failed += 1;
        std::cout << "A1 failed. Expected: " << 1 << "\nReceived: " << squareToRank(Square::A1) << "\n";
    }

    if (squareToRank(Square::H1) != 1) {
        failed += 1;
        std::cout << "H1 failed. Expected: " << 1 << "\nReceived: " << squareToRank(Square::H1) << "\n";
    }
    
    if (squareToRank(Square::E4) != 4) {
        failed += 1;
        std::cout << "E4 failed. Expected: " << 4 << "\nReceived: " << squareToRank(Square::E4) << "\n";
    }
    
    if (squareToRank(Square::A8) != 8) {
        failed += 1;
        std::cout << "A8 failed. Expected: " << 8 << "\nReceived: " << squareToRank(Square::A8) << "\n";
    }
    
    if (squareToRank(Square::H8) != 8) {
        failed += 1;
        std::cout << "H8 failed. Expected: " << 8 << "\nReceived: " << squareToRank(Square::H8) << "\n";
    }

    if (failed == 0) {
        std::cout << "All tests passed.\n";
    }

    return failed == 0;
}

bool testFile() {
    int failed = 0;

    if (squareToFile(Square::A1) != 'A') {
        failed += 1;
        std::cout << "A1 failed. Expected: 'A' \nReceived: " << squareToFile(Square::A1) << "\n";
    }
    
    if (squareToFile(Square::H1) != 'H') {
        failed += 1;
        std::cout << "H1 failed. Expected: 'H' \nReceived: " << squareToFile(Square::H1) << "\n";
    }
    
    if (squareToFile(Square::E4) != 'E') {
        failed += 1;
        std::cout << "E4 failed. Expected: 'E' \nReceived: " << squareToFile(Square::E4) << "\n";
    }
    
    if (squareToFile(Square::A8) != 'A') {
        failed += 1;
        std::cout << "A8 failed. Expected: 'A' \nReceived: " << squareToFile(Square::A8) << "\n";
    }
    
    if (squareToFile(Square::H8) != 'H') {
        failed += 1;
        std::cout << "H8 failed. Expected: 'H' \nReceived: " << squareToFile(Square::H8) << "\n";
    }

    if (failed == 0) {
        std::cout << "All tests passed.\n";
    }

    return failed == 0;
}