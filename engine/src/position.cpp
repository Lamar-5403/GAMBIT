#include <gambit/position.h>

Position::Position() :
    pieces{}, 
    sideToMove(Color::WHITE), 
    castlingRights(0b00001111), 
    enPassantSquare(std::nullopt), 
    halfMoveClock(0), 
    fullMoveNumber(1)
{
    initializeStartingPosition();
}

Bitboard& Position::getPieceBoard(Color color, PieceType piece) {
    return pieces[static_cast<uint8_t>(color)][static_cast<uint8_t>(piece)];
}

const Bitboard& Position::getPieceBoard(Color color, PieceType piece) const {
    return pieces[static_cast<uint8_t>(color)][static_cast<uint8_t>(piece)];
}

Bitboard Position::getOccupancy(Color color) const {
    Bitboard board = 0;

    for (int i = 0; i < 6; i++) {
        board |= pieces[static_cast<int>(color)][i];
    }

    return board;
}

Bitboard Position::getAllOccupancy() const {
    return getOccupancy(Color::WHITE) | getOccupancy(Color::BLACK);
}

Color Position::getSideToMove() const {
    return sideToMove;
}

std::optional<Square> Position::getEnPassantSquare() const {
    return enPassantSquare;
}

void Position::initializeStartingPosition() {
    getPieceBoard(Color::WHITE, PieceType::PAWN) = 
        squareToBitboard(Square::A2) | 
        squareToBitboard(Square::B2) | 
        squareToBitboard(Square::C2) | 
        squareToBitboard(Square::D2) | 
        squareToBitboard(Square::E2) | 
        squareToBitboard(Square::F2) | 
        squareToBitboard(Square::G2) | 
        squareToBitboard(Square::H2);

    getPieceBoard(Color::WHITE, PieceType::ROOK) = 
        squareToBitboard(Square::A1) | 
        squareToBitboard(Square::H1);

    getPieceBoard(Color::WHITE, PieceType::KNIGHT) = 
        squareToBitboard(Square::B1) | 
        squareToBitboard(Square::G1);

    getPieceBoard(Color::WHITE, PieceType::BISHOP) = 
        squareToBitboard(Square::C1) | 
        squareToBitboard(Square::F1);

    getPieceBoard(Color::WHITE, PieceType::QUEEN) = 
        squareToBitboard(Square::D1);

    getPieceBoard(Color::WHITE, PieceType::KING) = 
        squareToBitboard(Square::E1);

    getPieceBoard(Color::BLACK, PieceType::PAWN) = 
        squareToBitboard(Square::A7) | 
        squareToBitboard(Square::B7) | 
        squareToBitboard(Square::C7) | 
        squareToBitboard(Square::D7) | 
        squareToBitboard(Square::E7) | 
        squareToBitboard(Square::F7) | 
        squareToBitboard(Square::G7) | 
        squareToBitboard(Square::H7);

    getPieceBoard(Color::BLACK, PieceType::ROOK) = 
        squareToBitboard(Square::A8) | 
        squareToBitboard(Square::H8);

    getPieceBoard(Color::BLACK, PieceType::KNIGHT) = 
        squareToBitboard(Square::B8) | 
        squareToBitboard(Square::G8);

    getPieceBoard(Color::BLACK, PieceType::BISHOP) = 
        squareToBitboard(Square::C8) | 
        squareToBitboard(Square::F8);

    getPieceBoard(Color::BLACK, PieceType::QUEEN) = 
        squareToBitboard(Square::D8);

    getPieceBoard(Color::BLACK, PieceType::KING) = 
        squareToBitboard(Square::E8);
}