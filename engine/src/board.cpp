#include <gambit/board.h>

constexpr int BOARD_WIDTH = 8;

Bitboard squareToBitboard(Square square) {
    return 1ULL << static_cast<int>(square);
}

std::string squareToString(Square square) {
    int index = static_cast<int>(square);
    int rank = index / BOARD_WIDTH + 1;
    int file = index % BOARD_WIDTH;
    std::string letter = "Z";
    
    switch (file) {
        case 0:
            letter = "A";
        break;

        case 1:
            letter = "B";
        break;

        case 2:
            letter = "C";
        break;

        case 3:
            letter = "D";
        break;

        case 4:
            letter = "E";
        break;

        case 5:
            letter = "F";
        break;

        case 6:
            letter = "G";
        break;

        case 7:
            letter = "H";
        break;
    }

    std::string fileRank = letter + std::to_string(rank);
    return fileRank;
}