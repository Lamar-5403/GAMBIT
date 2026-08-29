#include <gambit/position.h>
#include <iostream>

constexpr Bitboard WHITE_PAWNS   = 0x00FF000000000000ULL;
constexpr Bitboard WHITE_ROOKS   = 0x8100000000000000ULL;
constexpr Bitboard WHITE_KNIGHTS = 0x4200000000000000ULL;
constexpr Bitboard WHITE_BISHOPS = 0x2400000000000000ULL;
constexpr Bitboard WHITE_QUEEN   = 0x0800000000000000ULL;
constexpr Bitboard WHITE_KING    = 0x1000000000000000ULL;

constexpr Bitboard BLACK_PAWNS   = 0x000000000000FF00ULL;
constexpr Bitboard BLACK_ROOKS   = 0x0000000000000081ULL;
constexpr Bitboard BLACK_KNIGHTS = 0x0000000000000042ULL;
constexpr Bitboard BLACK_BISHOPS = 0x0000000000000024ULL;
constexpr Bitboard BLACK_QUEEN   = 0x0000000000000008ULL;
constexpr Bitboard BLACK_KING    = 0x0000000000000010ULL;

bool testStartingPosition() {
    Position position;

    if (position.getPieceBoard(Color::WHITE, PieceType::PAWN) != WHITE_PAWNS) {
        std::cout << "White pawns failed.\n";
        return false;
    }

    if (position.getPieceBoard(Color::WHITE, PieceType::ROOK) != WHITE_ROOKS) {
        std::cout << "White rooks failed.\n";
        return false;
    }

    if (position.getPieceBoard(Color::WHITE, PieceType::KNIGHT) != WHITE_KNIGHTS) {
        std::cout << "White knights failed.\n";
        return false;
    }

    if (position.getPieceBoard(Color::WHITE, PieceType::BISHOP) != WHITE_BISHOPS) {
        std::cout << "White bishops failed.\n";
        return false;
    }

    if (position.getPieceBoard(Color::WHITE, PieceType::QUEEN) != WHITE_QUEEN) {
        std::cout << "White queen failed.\n";
        return false;
    }

    if (position.getPieceBoard(Color::WHITE, PieceType::KING) != WHITE_KING) {
        std::cout << "White king failed.\n";
        return false;
    }

    if (position.getPieceBoard(Color::BLACK, PieceType::PAWN) != BLACK_PAWNS) {
        std::cout << "Black pawns failed.\n";
        return false;
    }

    if (position.getPieceBoard(Color::BLACK, PieceType::ROOK) != BLACK_ROOKS) {
        std::cout << "Black rooks failed.\n";
        return false;
    }

    if (position.getPieceBoard(Color::BLACK, PieceType::KNIGHT) != BLACK_KNIGHTS) {
        std::cout << "Black knights failed.\n";
        return false;
    }

    if (position.getPieceBoard(Color::BLACK, PieceType::BISHOP) != BLACK_BISHOPS) {
        std::cout << "Black bishops failed.\n";
        return false;
    }

    if (position.getPieceBoard(Color::BLACK, PieceType::QUEEN) != BLACK_QUEEN) {
        std::cout << "Black queen failed.\n";
        return false;
    }

    if (position.getPieceBoard(Color::BLACK, PieceType::KING) != BLACK_KING) {
        std::cout << "Black king failed.\n";
        return false;
    }

    std::cout << "All tests passed.\n";
    return true;
}

