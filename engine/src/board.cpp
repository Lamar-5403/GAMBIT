#include <gambit/board.h>

std::ostream& operator<<(std::ostream& os, Square square) {
    os << squareToFile(square);
    os << static_cast<char>('0' + squareToRank(square));
    return os;
}

std::ostream& operator<<(std::ostream& os, Color color) {
    (color == Color::WHITE) ? os << "White" : os << "Black";
    return os;
}

std::ostream& operator<<(std::ostream& os, PieceType piece) {
    switch (piece) {
        case PieceType::PAWN:
            os << "Pawn";
        break;

        case PieceType::KNIGHT:
            os << "Knight";
        break;

        case PieceType::BISHOP:
            os << "Bishop";
        break;

        case PieceType::ROOK:
            os << "Rook";
        break;

        case PieceType::QUEEN:
            os << "Queen";
        break;

        case PieceType::KING:
            os << "King";
        break;

        default:
            os << "Undefined Piece Type";
        break;
    }

    return os;
}

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

Bitboard setSquare(Bitboard board, Square square){
    return board |= squareToBitboard(square);
}

Bitboard clearSquare(Bitboard board, Square square) {
    return board &= ~squareToBitboard(square);
}

bool isSquareOccupied(Bitboard board, Square square) {
    return (board & squareToBitboard(square)) != 0;
}