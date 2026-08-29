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

Square fileRankToSquare(char file, int rank) {
    return static_cast<Square>(NUM_SQUARES - (BOARD_SIZE * rank) + (file - 'A'));
}

bool isValidSquare(Square square) {
    // actual implementation deffered for now, placeholder function
    return true;
}

Bitboard setSquare(Bitboard board, Square square){
    return board |= squareToBitboard(square);
}

Bitboard clearSquare(Bitboard board, Square square) {
    return board &= ~squareToBitboard(square);
}

bool isSquareSet(Bitboard board, Square square) {
    return (board & squareToBitboard(square)) != 0;
}