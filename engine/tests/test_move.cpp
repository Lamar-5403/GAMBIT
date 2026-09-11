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