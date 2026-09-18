#include <gambit/position.h>
#include <iostream>
#include <bitset>

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
    Position position = Position::starting();

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

bool testStartingPositionFromFEN() {
    std::string fenString = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    Position fenPosition = positionFromFEN(fenString);
    Position startingPosition = Position::starting();

    int failed = 0;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            Bitboard fenBoard = fenPosition.getPieceBoard(static_cast<Color>(i), static_cast<PieceType>(j));
            Bitboard startBoard = startingPosition.getPieceBoard(static_cast<Color>(i), static_cast<PieceType>(j));
            if (fenBoard != startBoard) {
                std::cout << static_cast<Color>(i) << " " <<static_cast<PieceType>(j) << " failed. Expected: " << startBoard << ". Got: " << fenBoard << "\n";
                failed += 1;
            }
        }
    }

    if (fenPosition.getSideToMove() != Color::WHITE) {
        std::cout << "Expected White. Got " << fenPosition.getSideToMove() << "\n";
        failed += 1;
    }

    if (fenPosition.getCastlingRights() != 0b00001111) {
        std::cout << "Expected: " << std::bitset<8>(0b00001111) << ". Got: " << std::bitset<8>(fenPosition.getCastlingRights()) << "\n";
        failed += 1;
    }

    if (fenPosition.getEnPassantSquare() != std::nullopt) {
        std::cout << "Expected: NULL. Got: Target Square\n";
        failed += 1;
    }

    if (fenPosition.getHalfMoveClock() != 0) {
        std::cout << "Expected: 0. Got: " << fenPosition.getHalfMoveClock() << "\n";
        failed += 1;
    }

    if (fenPosition.getFullMoveNumber() != 1) {
        std::cout << "Expected: 1. Got: " << fenPosition.getFullMoveNumber() << "\n";
        failed += 1;
    }

    if (failed != 0) {
        std::cout << "FAIL: FEN Position\n";
        return false;
    }


    std::cout << "PASS: FEN Position\n";
    return true;

}

bool testPositionFromFEN() {
    std::string fenString = "r3k2r/p1ppq1b1/4pppp/4P3/PpNP4/2P2QP1/1P3P1P/R4RK1 b kq a3 0 15";
    Position fenPosition = positionFromFEN(fenString);
    int failed = 0;

    Bitboard whitePawns = 0x00A2440910000000;
    Bitboard whiteKnights = 0x0000000400000000;
    Bitboard whiteBishops = 0;
    Bitboard whiteRooks = 0x2100000000000000;
    Bitboard whiteQueen = 0x0000200000000000;
    Bitboard whiteKing = 0x4000000000000000;

    Bitboard blackPawns = 0x0000000200F00D00;
    Bitboard blackKnights = 0;
    Bitboard blackBishops = 0x0000000000004000;
    Bitboard blackRooks = 0x0000000000000081;
    Bitboard blackQueen = 0x0000000000001000;
    Bitboard blackKing = 0x0000000000000010;

    if (fenPosition.getPieceBoard(Color::WHITE, PieceType::PAWN) != whitePawns) {
        std::cout << "White pawns failed. Expected: " << std::hex << whitePawns << " Got: " << std::hex << fenPosition.getPieceBoard(Color::WHITE, PieceType::PAWN) << "\n";
        failed += 1;
    }

    if (fenPosition.getPieceBoard(Color::WHITE, PieceType::KNIGHT) != whiteKnights) {
        std::cout << "White knights failed. Expected: " << std::hex << whiteKnights << " Got: " << std::hex << fenPosition.getPieceBoard(Color::WHITE, PieceType::KNIGHT) << "\n";
        failed += 1;
    }

    if (fenPosition.getPieceBoard(Color::WHITE, PieceType::BISHOP) != whiteBishops) {
        std::cout << "White bishops failed. Expected: " << std::hex << whiteBishops << " Got: " << std::hex << fenPosition.getPieceBoard(Color::WHITE, PieceType::BISHOP) << "\n";
        failed += 1;
    }

    if (fenPosition.getPieceBoard(Color::WHITE, PieceType::ROOK) != whiteRooks) {
        std::cout << "White rooks failed. Expected: " << std::hex << whiteRooks << " Got: " << std::hex << fenPosition.getPieceBoard(Color::WHITE, PieceType::ROOK) << "\n";
        failed += 1;
    }

    if (fenPosition.getPieceBoard(Color::WHITE, PieceType::QUEEN) != whiteQueen) {
        std::cout << "White queen failed. Expected: " << std::hex << whiteQueen << " Got: " << std::hex << fenPosition.getPieceBoard(Color::WHITE, PieceType::QUEEN) << "\n";
        failed += 1;
    }

    if (fenPosition.getPieceBoard(Color::WHITE, PieceType::KING) != whiteKing) {
        std::cout << "White king failed. Expected: " << std::hex << whiteKing << " Got: " << std::hex << fenPosition.getPieceBoard(Color::WHITE, PieceType::KING) << "\n";
        failed += 1;
    }

    if (fenPosition.getPieceBoard(Color::BLACK, PieceType::PAWN) != blackPawns) {
        std::cout << "Black pawns failed. Expected: " << std::hex << blackPawns << " Got: " << std::hex << fenPosition.getPieceBoard(Color::BLACK, PieceType::PAWN) << "\n";
        failed += 1;
    }

    if (fenPosition.getPieceBoard(Color::BLACK, PieceType::KNIGHT) != blackKnights) {
        std::cout << "Black knights failed. Expected: " << std::hex << blackKnights << " Got: " << std::hex << fenPosition.getPieceBoard(Color::BLACK, PieceType::KNIGHT) << "\n";
        failed += 1;
    }

    if (fenPosition.getPieceBoard(Color::BLACK, PieceType::BISHOP) != blackBishops) {
        std::cout << "Black bishops failed. Expected: " << std::hex << blackBishops << " Got: " << std::hex << fenPosition.getPieceBoard(Color::BLACK, PieceType::BISHOP) << "\n";
        failed += 1;
    }

    if (fenPosition.getPieceBoard(Color::BLACK, PieceType::ROOK) != blackRooks) {
        std::cout << "Black rooks failed. Expected: " << std::hex << blackRooks << " Got: " << std::hex << fenPosition.getPieceBoard(Color::BLACK, PieceType::ROOK) << "\n";
        failed += 1;
    }

    if (fenPosition.getPieceBoard(Color::BLACK, PieceType::QUEEN) != blackQueen) {
        std::cout << "Black queen failed. Expected: " << std::hex << blackQueen << " Got: " << std::hex << fenPosition.getPieceBoard(Color::BLACK, PieceType::QUEEN) << "\n";
        failed += 1;
    }

    if (fenPosition.getPieceBoard(Color::BLACK, PieceType::KING) != blackKing) {
        std::cout << "Black king failed. Expected: " << std::hex << blackKing << " Got: " << std::hex << fenPosition.getPieceBoard(Color::BLACK, PieceType::KING) << "\n";
        failed += 1;
    }

    if (fenPosition.getSideToMove() != Color::BLACK) {
        std::cout << "Side to move failed. Expected: Black. Got: " << fenPosition.getSideToMove() << "\n";
        failed += 1;
    }

    if (fenPosition.getCastlingRights() != 0b00000011) {
        std::cout << "Castling rights failed. Expected: " << std::hex << 0b00000011 << ". Got: " << fenPosition.getCastlingRights() << "\n";
        failed += 1;
    }

    if (fenPosition.getEnPassantSquare() != Square::A3) {
        std::cout << "En Passant target failed. Expected: A3. Got: " << *fenPosition.getEnPassantSquare() << "\n";
        failed += 1;
    }

    if (fenPosition.getHalfMoveClock() != 0) {
        std::cout << "Half move clock failed. Expected: 0. Got: " << fenPosition.getHalfMoveClock() << "\n";
        failed += 1;
    }

    if (fenPosition.getFullMoveNumber() != 15) {
        std::cout << "Full move number failed. Expected: 15. Got: " << std::dec << fenPosition.getFullMoveNumber() << "\n";
        failed += 1;
    }

    if (failed != 0) {
        return false;
    }

    return true;
}