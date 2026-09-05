#include <gambit/position.h>
#include <gambit/move.h>
#include <iostream>

bool testMakeMove() {
    Position position = Position::starting();

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

            if (isSquareOccupied(pawns, square)) {
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

            if (isSquareOccupied(pawns, square)) {
                std::cout << squareToFile(square) << squareToRank(square) << " ";
            }
        }
    }

    std::cout << "\n";

    return true;
}

bool testForwardPawnMove() {
    Position position = Position::starting();

    std::vector<Move> moves;

    generatePawnMoves(position, moves);

    for (const Move& move : moves) {
        std::cout << move << "\n";
    }

    std::cout << "Total moves: " << moves.size() << "\n";

    return true;
}

bool testPseudoLegalPawnMoves() {
    Position position = positionFromFEN("r3kb1r/pbpqp1P1/1pn5/PB1pPp1p/3Pn3/5N1p/1PP2P2/RNBQK2R w KQkq f6 0 2");

    std::vector<Move> moves;

    generatePawnMoves(position, moves);

    for (const Move& move : moves) {
        std::cout << move << "\n";
    }

    std::cout << "Total moves: " << moves.size() << "\n";

    return true;
}