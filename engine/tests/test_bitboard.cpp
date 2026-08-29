#include <gambit/board.h>
#include <iostream>
#include <bitset>

bool testBoard() {
    int failed = 0;

    Bitboard A1_board = squareToBitboard(Square::A1);
    Bitboard A1_expected = 1ULL << 56;
    if (A1_board != A1_expected) {
        std::cout << "A1 failed. Expected: " << A1_expected << "\nReceived: " << A1_board << "\n";
    }
    Bitboard H1_board = squareToBitboard(Square::H1);
    Bitboard H1_expected = 1ULL << 63;
    if (H1_board != H1_expected) {
        std::cout << "H1 failed. Expected: " << H1_expected << "\nReceived: " << H1_board << "\n";
    }
    Bitboard E4_board = squareToBitboard(Square::E4);
    Bitboard E4_expected = 1ULL << 36;
    if (E4_board != E4_expected) {
        std::cout << "E4 failed. Expected: " << E4_expected << "\nReceived: " << E4_board << "\n";
    }
    Bitboard A8_board = squareToBitboard(Square::A8);
    Bitboard A8_expected = 1ULL << 0;
    if (A8_board != A8_expected) {
        std::cout << "A8 failed. Expected: " << A8_expected << "\nReceived: " << A8_board << "\n";
    }
    Bitboard H8_board = squareToBitboard(Square::H8);
    Bitboard H8_expected = 1ULL << 7;
    if (H8_board != H8_expected) {
        std::cout << "H8 failed. Expected: " << H8_expected << "\nReceived: " << H8_board << "\n";
    }

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

    int A1_rank = squareToRank(Square::A1);
    int A1_expected = 1;
    if (A1_rank != A1_expected) {
        failed += 1;
        std::cout << "A1 failed. Expected: " << A1_expected << "\nReceived: " << A1_rank << "\n";
    }
    int H1_rank = squareToRank(Square::H1);
    int H1_expected = 1;
    if (H1_rank != H1_expected) {
        failed += 1;
        std::cout << "H1 failed. Expected: " << H1_expected << "\nReceived: " << H1_rank << "\n";
    }
    int E4_rank = squareToRank(Square::E4);
    int E4_expected = 4;
    if (E4_rank != E4_expected) {
        failed += 1;
        std::cout << "E4 failed. Expected: " << E4_expected << "\nReceived: " << E4_rank << "\n";
    }
    int A8_rank = squareToRank(Square::A8);
    int A8_expected = 8;
    if (A8_rank != A8_expected) {
        failed += 1;
        std::cout << "A8 failed. Expected: " << A8_expected << "\nReceived: " << A8_rank << "\n";
    }
    int H8_rank = squareToRank(Square::H8);
    int H8_expected = 8;
    if (H8_rank != H8_expected) {
        failed += 1;
        std::cout << "H8 failed. Expected: " << H8_expected << "\nReceived: " << H8_rank << "\n";
    }

    if (failed == 0) {
        std::cout << "All tests passed.\n";
    }

    return failed == 0;
}

bool testFile() {
    int failed = 0;

    char A1_file = squareToFile(Square::A1);
    char A1_expected = 'A';
    if (A1_file != A1_expected) {
        failed += 1;
        std::cout << "A1 failed. Expected: " << A1_expected << "\nReceived: " << A1_file << "\n";
    }
    char H1_file = squareToFile(Square::H1);
    char H1_expected = 'H';
    if (H1_file != H1_expected) {
        failed += 1;
        std::cout << "H1 failed. Expected: " << H1_expected << "\nReceived: " << H1_file << "\n";
    }
    char E4_file = squareToFile(Square::E4);
    char E4_expected = 'E';
    if (E4_file != E4_expected) {
        failed += 1;
        std::cout << "E4 failed. Expected: " << E4_expected << "\nReceived: " << E4_file << "\n";
    }
    char A8_file = squareToFile(Square::A8);
    char A8_expected = 'A';
    if (A8_file != A8_expected) {
        failed += 1;
        std::cout << "A8 failed. Expected: " << A8_expected << "\nReceived: " << A8_file << "\n";
    }
    char H8_file = squareToFile(Square::H8);
    char H8_expected = 'H';
    if (H8_file != H8_expected) {
        failed += 1;
        std::cout << "H8 failed. Expected: " << H8_expected << "\nReceived: " << H8_file << "\n";
    }

    if (failed == 0) {
        std::cout << "All tests passed.\n";
    }

    return failed == 0;
}