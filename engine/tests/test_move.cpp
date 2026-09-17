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

bool testEnPassant() {
    Position position = positionFromFEN("rnbqkbnr/ppp2ppp/4p3/3pP3/8/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 3");
    Move expectedMove = {
        Square::E5,
        Square::D6,
        Color::WHITE,
        PieceType::PAWN,
        MoveType::EN_PASSANT,
        std::nullopt
    };

    std::vector<Move> moves;

    generatePawnMoves(position, moves);
    int enPassantMovesFound = 0;

    for (const Move& move : moves) {
        if (move.type == MoveType::EN_PASSANT) {
            ++enPassantMovesFound;

            if (move != expectedMove) {
                std::cout << move << "\n";
                return false;
            }

            std::cout << move << "\n";
        }
    }

    if (enPassantMovesFound != 1) {
        return false;
    }

    moves.clear();

    position = positionFromFEN("rnbqkbnr/pppp2pp/4p3/4Pp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3");
    expectedMove = {
        Square::E5,
        Square::F6,
        Color::WHITE,
        PieceType::PAWN,
        MoveType::EN_PASSANT,
        std::nullopt
    };

    generatePawnMoves(position, moves);
    enPassantMovesFound = 0;

    for (const Move& move : moves) {
        if (move.type == MoveType::EN_PASSANT) {
            ++enPassantMovesFound;

            if (move != expectedMove) {
                std::cout << move << "\n";
                return false;
            }

            std::cout << move << "\n";
        }
    }

    if (enPassantMovesFound != 1) {
        return false;
    }

    moves.clear();

    position = positionFromFEN("rnbqkbnr/ppp1pppp/8/8/3pP3/3P4/PPP2PPP/RNBQKBNR b KQkq e3 0 3");
    expectedMove = {
        Square::D4,
        Square::E3,
        Color::BLACK,
        PieceType::PAWN,
        MoveType::EN_PASSANT,
        std::nullopt
    };

    generatePawnMoves(position, moves);
    enPassantMovesFound = 0;

    for (const Move& move : moves) {
        if (move.type == MoveType::EN_PASSANT) {
            ++enPassantMovesFound;

            if (move != expectedMove) {
                std::cout << move << "\n";
                return false;
            }

            std::cout << move << "\n";
        }
    }

    if (enPassantMovesFound != 1) {
        return false;
    }

    moves.clear();

    position = positionFromFEN("rnbqkbnr/ppp1pppp/8/8/2Pp4/3P4/PP2PPPP/RNBQKBNR b KQkq c3 0 3");
    expectedMove = {
        Square::D4,
        Square::C3,
        Color::BLACK,
        PieceType::PAWN,
        MoveType::EN_PASSANT,
        std::nullopt
    };

    generatePawnMoves(position, moves);
    enPassantMovesFound = 0;

    for (const Move& move : moves) {
        if (move.type == MoveType::EN_PASSANT) {
            ++enPassantMovesFound;

            if (move != expectedMove) {
                std::cout << move << "\n";
                return false;
            }

            std::cout << move << "\n";
        }
    }

    if (enPassantMovesFound != 1) {
        return false;
    }

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

bool testPseudoLegalKnightMoves() {
    Position position = positionFromFEN("n3Qrk1/5ppp/3nN3/1n3b2/8/5N2/5PPP/N4RK1 b - - 14 26");

    std::vector<Move> expectedMoves = {
        {Square::A8, Square::C7, Color::BLACK, PieceType::KNIGHT, MoveType::QUIET, std::nullopt},
        {Square::A8, Square::B6, Color::BLACK, PieceType::KNIGHT, MoveType::QUIET, std::nullopt},
        {Square::D6, Square::E8, Color::BLACK, PieceType::KNIGHT, MoveType::CAPTURE, std::nullopt},
        {Square::D6, Square::C8, Color::BLACK, PieceType::KNIGHT, MoveType::QUIET, std::nullopt},
        {Square::D6, Square::B7, Color::BLACK, PieceType::KNIGHT, MoveType::QUIET, std::nullopt},
        {Square::D6, Square::C4, Color::BLACK, PieceType::KNIGHT, MoveType::QUIET, std::nullopt},
        {Square::D6, Square::E4, Color::BLACK, PieceType::KNIGHT, MoveType::QUIET, std::nullopt},
        {Square::B5, Square::A7, Color::BLACK, PieceType::KNIGHT, MoveType::QUIET, std::nullopt},
        {Square::B5, Square::C7, Color::BLACK, PieceType::KNIGHT, MoveType::QUIET, std::nullopt},
        {Square::B5, Square::D4, Color::BLACK, PieceType::KNIGHT, MoveType::QUIET, std::nullopt},
        {Square::B5, Square::C3, Color::BLACK, PieceType::KNIGHT, MoveType::QUIET, std::nullopt},
        {Square::B5, Square::A3, Color::BLACK, PieceType::KNIGHT, MoveType::QUIET, std::nullopt},
    };

    std::vector<Move> actualMoves;

    generateKingMoves(position, actualMoves);

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

bool testStandardKingMoves() {
    Position position = positionFromFEN("Kr6/8/6k1/8/4NQ2/8/8/8 w - - 0 1");

    std::vector<Move> expectedMoves = {
        {Square::A8, Square::B8, Color::WHITE, PieceType::KING, MoveType::CAPTURE, std::nullopt},
        {Square::A8, Square::A7, Color::WHITE, PieceType::KING, MoveType::QUIET, std::nullopt},
        {Square::A8, Square::B7, Color::WHITE, PieceType::KING, MoveType::QUIET, std::nullopt}
    };

    std::vector<Move> actualMoves;

    generateKingMoves(position, actualMoves);

    if (expectedMoves.size() != actualMoves.size()) {
        return false;
    }

    for (const Move& expected : expectedMoves) {
        if (std::find(actualMoves.begin(), actualMoves.end(), expected) == actualMoves.end()) {
            return false;
        }
    }

    expectedMoves.clear();
    actualMoves.clear();

    position = positionFromFEN("8/6k1/2p5/3Bq3/3Kn3/4R3/8/8 w - - 0 1");

    expectedMoves = {
        {Square::D4, Square::C5, Color::WHITE, PieceType::KING, MoveType::QUIET, std::nullopt},
        {Square::D4, Square::E5, Color::WHITE, PieceType::KING, MoveType::CAPTURE, std::nullopt},
        {Square::D4, Square::C4, Color::WHITE, PieceType::KING, MoveType::QUIET, std::nullopt},
        {Square::D4, Square::E4, Color::WHITE, PieceType::KING, MoveType::CAPTURE, std::nullopt},
        {Square::D4, Square::C3, Color::WHITE, PieceType::KING, MoveType::QUIET, std::nullopt},
        {Square::D4, Square::D3, Color::WHITE, PieceType::KING, MoveType::QUIET, std::nullopt}
    };

    generateKingMoves(position, actualMoves);

    if (expectedMoves.size() != actualMoves.size()) {
        return false;
    }

    for (const Move& expected : expectedMoves) {
        if (std::find(actualMoves.begin(), actualMoves.end(), expected) == actualMoves.end()) {
            return false;
        }
    }

    expectedMoves.clear();
    actualMoves.clear();

    position = positionFromFEN("8/2K5/8/8/6N1/7k/6r1/8 b - - 0 1");

    expectedMoves = {
        {Square::H3, Square::G4, Color::BLACK, PieceType::KING, MoveType::CAPTURE, std::nullopt},
        {Square::H3, Square::H4, Color::BLACK, PieceType::KING, MoveType::QUIET, std::nullopt},
        {Square::H3, Square::G3, Color::BLACK, PieceType::KING, MoveType::QUIET, std::nullopt},
        {Square::H3, Square::H2, Color::BLACK, PieceType::KING, MoveType::QUIET, std::nullopt}
    };

    generateKingMoves(position, actualMoves);

    if (expectedMoves.size() != actualMoves.size()) {
        return false;
    }

    for (const Move& expected : expectedMoves) {
        if (std::find(actualMoves.begin(), actualMoves.end(), expected) == actualMoves.end()) {
            return false;
        }
    }

    std::cout << "PASS: Standard King moves.\n";
    return true;
}

bool testGenerateBishopMoves() {
    Position position = positionFromFEN("7R/5k1q/3Q4/4b3/4B3/5rR1/2n5/7K w - - 0 1");
    std::vector<Move> actualMoves = {};

    generateBishopMoves(position, actualMoves);

    std::vector<Move> expectedMoves = {
        {Square::E4, Square::F5, Color::WHITE, PieceType::BISHOP, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::G6, Color::WHITE, PieceType::BISHOP, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::H7, Color::WHITE, PieceType::BISHOP, MoveType::CAPTURE, std::nullopt},
        {Square::E4, Square::F3, Color::WHITE, PieceType::BISHOP, MoveType::CAPTURE, std::nullopt},
        {Square::E4, Square::D3, Color::WHITE, PieceType::BISHOP, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::C2, Color::WHITE, PieceType::BISHOP, MoveType::CAPTURE, std::nullopt},
        {Square::E4, Square::D5, Color::WHITE, PieceType::BISHOP, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::C6, Color::WHITE, PieceType::BISHOP, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::B7, Color::WHITE, PieceType::BISHOP, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::A8, Color::WHITE, PieceType::BISHOP, MoveType::QUIET, std::nullopt}
    };

    if (expectedMoves.size() != actualMoves.size()) {
        return false;
    }

    for (const Move& expected : expectedMoves) {
        if (std::find(actualMoves.begin(), actualMoves.end(), expected) == actualMoves.end()) {
            return false;
        }
    }

    std::cout << "PASS: Generate bishop moves.\n";
    return true;
}

bool testGenerateRookMoves() {
    Position position = positionFromFEN("8/4r1k1/8/8/4Rn2/3b4/4Q3/7K w - - 0 1");
    std::vector<Move> actualMoves = {};

    generateRookMoves(position, actualMoves);

    std::vector<Move> expectedMoves = {
        {Square::E4, Square::E5, Color::WHITE, PieceType::ROOK, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::E6, Color::WHITE, PieceType::ROOK, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::E7, Color::WHITE, PieceType::ROOK, MoveType::CAPTURE, std::nullopt},
        {Square::E4, Square::E3, Color::WHITE, PieceType::ROOK, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::F4, Color::WHITE, PieceType::ROOK, MoveType::CAPTURE, std::nullopt},
        {Square::E4, Square::D4, Color::WHITE, PieceType::ROOK, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::C4, Color::WHITE, PieceType::ROOK, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::B4, Color::WHITE, PieceType::ROOK, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::A4, Color::WHITE, PieceType::ROOK, MoveType::QUIET, std::nullopt},
    };

    if (expectedMoves.size() != actualMoves.size()) {
        return false;
    }

    for (const Move& expected : expectedMoves) {
        if (std::find(actualMoves.begin(), actualMoves.end(), expected) == actualMoves.end()) {
            return false;
        }
    }

    std::cout << "PASS: Generate rook moves.\n";
    return true;
}

bool testGenerateQueenMoves() {
    Position position = positionFromFEN("N3r1k1/7n/8/8/p3Qb2/8/2p3K1/8 w - - 0 1");
    std::vector<Move> actualMoves = {};

    generateQueenMoves(position, actualMoves);

    std::vector<Move> expectedMoves = {
        {Square::E4, Square::E5, Color::WHITE, PieceType::QUEEN, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::E6, Color::WHITE, PieceType::QUEEN, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::E7, Color::WHITE, PieceType::QUEEN, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::E8, Color::WHITE, PieceType::QUEEN, MoveType::CAPTURE, std::nullopt},
        {Square::E4, Square::F5, Color::WHITE, PieceType::QUEEN, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::G6, Color::WHITE, PieceType::QUEEN, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::H7, Color::WHITE, PieceType::QUEEN, MoveType::CAPTURE, std::nullopt},
        {Square::E4, Square::F4, Color::WHITE, PieceType::QUEEN, MoveType::CAPTURE, std::nullopt},
        {Square::E4, Square::F3, Color::WHITE, PieceType::QUEEN, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::E3, Color::WHITE, PieceType::QUEEN, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::E2, Color::WHITE, PieceType::QUEEN, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::E1, Color::WHITE, PieceType::QUEEN, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::D3, Color::WHITE, PieceType::QUEEN, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::C2, Color::WHITE, PieceType::QUEEN, MoveType::CAPTURE, std::nullopt},
        {Square::E4, Square::D4, Color::WHITE, PieceType::QUEEN, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::C4, Color::WHITE, PieceType::QUEEN, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::B4, Color::WHITE, PieceType::QUEEN, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::A4, Color::WHITE, PieceType::QUEEN, MoveType::CAPTURE, std::nullopt},
        {Square::E4, Square::D5, Color::WHITE, PieceType::QUEEN, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::C6, Color::WHITE, PieceType::QUEEN, MoveType::QUIET, std::nullopt},
        {Square::E4, Square::B7, Color::WHITE, PieceType::QUEEN, MoveType::QUIET, std::nullopt},
    };

    if (expectedMoves.size() != actualMoves.size()) {
        return false;
    }

    for (const Move& expected : expectedMoves) {
        if (std::find(actualMoves.begin(), actualMoves.end(), expected) == actualMoves.end()) {
            return false;
        }
    }

    std::cout << "PASS: Generate queen moves.\n";
    return true;
}

bool testCastling() {
    bool passed = true;
    Position position = positionFromFEN("rnbqk2r/pppp1ppp/3b1n2/4p3/4P3/3B1N2/PPPP1PPP/RNBQK2R w KQkq - 4 4"); // valid O-O, blocked O-O-O
    std::vector<Move> actualMoves = {};
    std::vector<Move> expectedMoves = {
        {Square::E1, Square::E2, Color::WHITE, PieceType::KING, MoveType::QUIET, std::nullopt},
        {Square::E1, Square::F1, Color::WHITE, PieceType::KING, MoveType::QUIET, std::nullopt},
        {Square::E1, Square::G1, Color::WHITE, PieceType::KING, MoveType::CASTLE, std::nullopt}
    };

    generateKingMoves(position, actualMoves);

    if (expectedMoves.size() != actualMoves.size()) {
        std::cout << "FAIL: valid O-O.\n";
        passed &= false;
    }

    for (const Move& expected : expectedMoves) {
        if (std::find(actualMoves.begin(), actualMoves.end(), expected) == actualMoves.end()) {
            std::cout << "FAIL: valid O-O.\n";
            passed &= false;
        }
    }

    expectedMoves.clear();
    actualMoves.clear();
    position = positionFromFEN("r1bqk2r/p1pp1ppp/1pnb1n2/4p3/4P3/3B1N2/PPPP1PPP/RNBQK2R w Qkq - 0 6"); // no castling right O-O, pieces blocking O-O-O

    expectedMoves = {
        {Square::E1, Square::E2, Color::WHITE, PieceType::KING, MoveType::QUIET, std::nullopt},
        {Square::E1, Square::F1, Color::WHITE, PieceType::KING, MoveType::QUIET, std::nullopt}
    };

    generateKingMoves(position, actualMoves);

    if (expectedMoves.size() != actualMoves.size()) {
        std::cout << "FAIL: no castling right O-O, pieces blocking O-O-O.\n";
        passed &= false;
    }

    for (const Move& expected : expectedMoves) {
        if (std::find(actualMoves.begin(), actualMoves.end(), expected) == actualMoves.end()) {
            std::cout << "FAIL: no castling right O-O, pieces blocking O-O-O.\n";
            passed &= false;
        }
    }

    expectedMoves.clear();
    actualMoves.clear();
    position = positionFromFEN("rnb1k2r/p1ppqppp/1p3n2/1Bb1p3/4P3/5P1N/PPPP2PP/RNBQK2R w KQkq - 0 1"); // G1 attacked, rights exist

    expectedMoves = {
        {Square::E1, Square::E2, Color::WHITE, PieceType::KING, MoveType::QUIET, std::nullopt},
        {Square::E1, Square::F1, Color::WHITE, PieceType::KING, MoveType::QUIET, std::nullopt},
        {Square::E1, Square::F2, Color::WHITE, PieceType::KING, MoveType::QUIET, std::nullopt}
    };

    generateKingMoves(position, actualMoves);

    if (expectedMoves.size() != actualMoves.size()) {
        std::cout << "FAIL: O-O rights exist, G1 attacked.\n";
        passed &= false;
    }

    for (const Move& expected : expectedMoves) {
        if (std::find(actualMoves.begin(), actualMoves.end(), expected) == actualMoves.end()) {
            std::cout << "FAIL: O-O rights exist, G1 attacked.\n";
            passed &= false;
        }
    }

    expectedMoves.clear();
    actualMoves.clear();
    position = positionFromFEN("rnbqkb1r/pppp1ppp/8/4p3/2B1P3/4nP1N/PPPP2PP/RNBQK2R w KQkq - 3 5"); // O-O rights exist, F1 attacked

    expectedMoves = {
        {Square::E1, Square::E2, Color::WHITE, PieceType::KING, MoveType::QUIET, std::nullopt},
        {Square::E1, Square::F1, Color::WHITE, PieceType::KING, MoveType::QUIET, std::nullopt},
        {Square::E1, Square::F2, Color::WHITE, PieceType::KING, MoveType::QUIET, std::nullopt}
    };

    generateKingMoves(position, actualMoves);

    if (expectedMoves.size() != actualMoves.size()) {
        std::cout << "FAIL: O-O rights exist, F1 attacked.\n";
        passed &= false;
    }

    for (const Move& expected : expectedMoves) {
        if (std::find(actualMoves.begin(), actualMoves.end(), expected) == actualMoves.end()) {
            std::cout << "FAIL: O-O rights exist, F1 attacked.\n";
            passed &= false;
        }
    }

    expectedMoves.clear();
    actualMoves.clear();
    position = positionFromFEN("r3kbnr/pppbpppp/2nq4/3p4/3P1B2/2NQ4/PPP1PPPP/R3KBNR w KQkq - 6 5"); // valid O-O-O

    expectedMoves = {
        {Square::E1, Square::D1, Color::WHITE, PieceType::KING, MoveType::QUIET, std::nullopt},
        {Square::E1, Square::D2, Color::WHITE, PieceType::KING, MoveType::QUIET, std::nullopt},
        {Square::E1, Square::C1, Color::WHITE, PieceType::KING, MoveType::CASTLE, std::nullopt}
    };

    generateKingMoves(position, actualMoves);

    if (expectedMoves.size() != actualMoves.size()) {
        std::cout << "FAIL: Valid O-O-O.\n";
        passed &= false;
    }

    for (const Move& expected : expectedMoves) {
        if (std::find(actualMoves.begin(), actualMoves.end(), expected) == actualMoves.end()) {
            std::cout << "FAIL: Valid O-O-O.\n";
            passed &= false;
        }
    }

    expectedMoves.clear();
    actualMoves.clear();
    position = positionFromFEN("r3k2r/pppbqppp/2nbpn2/3p4/3P4/1PNBPN2/P1PB1PPP/R2Q1RK1 b kq - 0 8"); // valid O-O-O and O-O black

    expectedMoves = {
        {Square::E8, Square::D8, Color::BLACK, PieceType::KING, MoveType::QUIET, std::nullopt},
        {Square::E8, Square::F8, Color::BLACK, PieceType::KING, MoveType::QUIET, std::nullopt},
        {Square::E8, Square::C8, Color::BLACK, PieceType::KING, MoveType::CASTLE, std::nullopt},
        {Square::E8, Square::G8, Color::BLACK, PieceType::KING, MoveType::CASTLE, std::nullopt}
    };

    generateKingMoves(position, actualMoves);

    if (expectedMoves.size() != actualMoves.size()) {
        std::cout << "FAIL: Valid O-O-O and O-O black.\n";
        passed &= false;
    }

    for (const Move& expected : expectedMoves) {
        if (std::find(actualMoves.begin(), actualMoves.end(), expected) == actualMoves.end()) {
            std::cout << "FAIL: Valid O-O-O and O-O black.\n";
            passed &= false;
        }
    }

    expectedMoves.clear();
    actualMoves.clear();
    position = positionFromFEN("r3k3/pppbqppp/2nbpn2/3p4/3P4/1PNBPN2/P1PB1PPP/R2Q1RK1 b kq - 0 8"); // both black castling rights exist, no rook on H8

    expectedMoves = {
        {Square::E8, Square::D8, Color::BLACK, PieceType::KING, MoveType::QUIET, std::nullopt},
        {Square::E8, Square::F8, Color::BLACK, PieceType::KING, MoveType::QUIET, std::nullopt},
        {Square::E8, Square::C8, Color::BLACK, PieceType::KING, MoveType::CASTLE, std::nullopt}
    };

    generateKingMoves(position, actualMoves);

    if (expectedMoves.size() != actualMoves.size()) {
        std::cout << "FAIL: Valid O-O-O, no rook on H8.\n";
        passed &= false;
    }

    for (const Move& expected : expectedMoves) {
        if (std::find(actualMoves.begin(), actualMoves.end(), expected) == actualMoves.end()) {
            std::cout << "FAIL: Valid O-O-O, no rook on H8.\n";
            passed &= false;
        }
    }

    if (passed) {
        std::cout << "PASS: King castling generation.\n";
    }

    return passed;
}