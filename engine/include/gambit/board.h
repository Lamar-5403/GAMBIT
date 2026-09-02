#pragma once
#include <cstdint>

using Bitboard = std::uint64_t;

constexpr int NUM_SQUARES = 64;
constexpr int BOARD_SIZE = 8;

enum class Square {
    A8, B8, C8, D8, E8, F8, G8, H8,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A2, B2, C2, D2, E2, F2, G2, H2, 
    A1, B1, C1, D1, E1, F1, G1, H1,
};

enum class Color {
    WHITE = 0,
    BLACK = 1
};

enum class PieceType {
    PAWN = 0,
    KNIGHT = 1,
    BISHOP = 2,
    ROOK = 3,
    QUEEN = 4,
    KING = 5
};

Bitboard squareToBitboard(Square square);
int squareToRank(Square square);
char squareToFile(Square square);
Square fileRankToSquare(char file, int rank);
bool isValidSquare(Square square);
Bitboard setSquare(Bitboard board, Square square);
Bitboard clearSquare(Bitboard board, Square square);
bool isSquareOccupied(Bitboard board, Square square);