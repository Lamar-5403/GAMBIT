#include <gambit/position.h>
#include <gambit/move.h>
#include <iostream>

bool testMakeMove() {
    Position position;

    Move move {
        Square::E2,
        Square::E4,
        Color::WHITE,
        PieceType::PAWN,
        MoveType::QUIET,
        std::nullopt
    };

    makeMove(position, move);

    Bitboard pawns = position.getPieceBoard(Color::WHITE, PieceType::PAWN);

    std::cout << "White Pawns: ";

    for (char file = 'A'; file <= 'H'; file++) {
        for (int rank = 8; rank >= 1; rank--) {
            Square square = fileRankToSquare(file, rank);

            if (isSquareSet(pawns, square)) {
                std::cout << squareToFile(square) << squareToRank(square) << " ";
            }
        }
    }

    std::cout << "\n";

    unmakeMove(position, move);

    pawns = position.getPieceBoard(Color::WHITE, PieceType::PAWN);

    std::cout << "White Pawns: ";

    for (char file = 'A'; file <= 'H'; file++) {
        for (int rank = 8; rank >= 1; rank--) {
            Square square = fileRankToSquare(file, rank);

            if (isSquareSet(pawns, square)) {
                std::cout << squareToFile(square) << squareToRank(square) << " ";
            }
        }
    }

    std::cout << "\n";

    return true;
}