#include <gambit/board.h>

Bitboard squareToBitboard(Square square) {
    return 1ULL << static_cast<int>(square);
}

int squareToRank(Square square) {
    return BOARD_SIZE - (static_cast<int>(square) / BOARD_SIZE);
}

char squareToFile(Square square) {
    return 'A' + (static_cast<int>(square) % BOARD_SIZE);
}