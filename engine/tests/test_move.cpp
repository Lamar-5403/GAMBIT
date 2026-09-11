#include <gambit/position.h>
#include <gambit/move.h>
#include <iostream>
#include <algorithm>

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
    Position position = positionFromFEN("r3kb1r/pbpqp1P1/1pn5/PB1pPp1p/3Pn3/5N1p/1PP2P2/RNBQK2R w KQkq f6 0 28");

    std::vector<Move> expectedMoves = {
        {Square::A5, Square::A6, Color::WHITE, PieceType::PAWN, MoveType::QUIET, std::nullopt},
        {Square::A5, Square::B6, Color::WHITE, PieceType::PAWN, MoveType::CAPTURE, std::nullopt},
        {Square::B2, Square::B3, Color::WHITE, PieceType::PAWN, MoveType::QUIET, std::nullopt},
        {Square::B2, Square::B4, Color::WHITE, PieceType::PAWN, MoveType::DOUBLE_PAWN_PUSH, std::nullopt},
        {Square::C2, Square::C3, Color::WHITE, PieceType::PAWN, MoveType::QUIET, std::nullopt},
        {Square::C2, Square::C4, Color::WHITE, PieceType::PAWN, MoveType::DOUBLE_PAWN_PUSH, std::nullopt},
        {Square::E5, Square::E6, Color::WHITE, PieceType::PAWN, MoveType::QUIET, std::nullopt},
        {Square::E5, Square::F6, Color::WHITE, PieceType::PAWN, MoveType::EN_PASSANT, std::nullopt},
        {Square::G7, Square::F8, Color::WHITE, PieceType::PAWN, MoveType::PROMOTION_CAPTURE, PieceType::BISHOP},
        {Square::G7, Square::F8, Color::WHITE, PieceType::PAWN, MoveType::PROMOTION_CAPTURE, PieceType::KNIGHT},
        {Square::G7, Square::F8, Color::WHITE, PieceType::PAWN, MoveType::PROMOTION_CAPTURE, PieceType::ROOK},
        {Square::G7, Square::F8, Color::WHITE, PieceType::PAWN, MoveType::PROMOTION_CAPTURE, PieceType::QUEEN},
        {Square::G7, Square::G8, Color::WHITE, PieceType::PAWN, MoveType::PROMOTION, PieceType::BISHOP},
        {Square::G7, Square::G8, Color::WHITE, PieceType::PAWN, MoveType::PROMOTION, PieceType::KNIGHT},
        {Square::G7, Square::G8, Color::WHITE, PieceType::PAWN, MoveType::PROMOTION, PieceType::ROOK},
        {Square::G7, Square::G8, Color::WHITE, PieceType::PAWN, MoveType::PROMOTION, PieceType::QUEEN},
        {Square::G7, Square::H8, Color::WHITE, PieceType::PAWN, MoveType::PROMOTION_CAPTURE, PieceType::BISHOP},
        {Square::G7, Square::H8, Color::WHITE, PieceType::PAWN, MoveType::PROMOTION_CAPTURE, PieceType::KNIGHT},
        {Square::G7, Square::H8, Color::WHITE, PieceType::PAWN, MoveType::PROMOTION_CAPTURE, PieceType::ROOK},
        {Square::G7, Square::H8, Color::WHITE, PieceType::PAWN, MoveType::PROMOTION_CAPTURE, PieceType::QUEEN},
    };

    std::vector<Move> actualMoves;

    generatePawnMoves(position, actualMoves);

    if (expectedMoves.size() != actualMoves.size()) {
        return false;
    }

    for (const Move& expected : expectedMoves) {
        if (std::find(actualMoves.begin(), actualMoves.end(), expected) == actualMoves.end()) {
            return false;
        }
    }

    return true;
}