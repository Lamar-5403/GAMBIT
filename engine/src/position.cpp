#include <gambit/position.h>
#include <cctype>
#include <sstream>

Position::Position() :
    pieces{}, 
    sideToMove(Color::WHITE), 
    castlingRights(0), 
    enPassantSquare(std::nullopt), 
    halfMoveClock(0), 
    fullMoveNumber(1)
{
}

Position Position::starting() {
    Position position;
    position.initializeStartingPosition();
    position.castlingRights = 0b00001111;

    return position;
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

std::uint8_t Position::getCastlingRights() const {
    return castlingRights;
}

std::optional<Square> Position::getEnPassantSquare() const {
    return enPassantSquare;
}

int Position::getHalfMoveClock() const {
    return halfMoveClock;
}
int Position::getFullMoveNumber() const {
    return fullMoveNumber;
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

std::uint8_t addCastlingRight(char c, std::uint8_t rights) {
    switch (c) {
        case 'K':
            rights |= 0b00001000;
        break;

        case 'Q':
            rights |= 0b00000100;
        break;

        case 'k':
            rights |= 0b00000010;
        break;

        case 'q':
            rights |= 0b00000001;
        break;

        default:
        break;
    }

    return rights;
}

PieceType charToPieceType(char c) {
    switch (c) {
        case 'r':
            return PieceType::ROOK;

        case 'n':
            return PieceType::KNIGHT;

        case 'b':
            return PieceType::BISHOP;

        case 'q':
            return PieceType::QUEEN;

        case 'k':
            return PieceType::KING;

        default:
            return PieceType::PAWN;
    }
}

Position positionFromFEN(std::string FENstring) {
    Position position;
    int index = 0;

    std::istringstream stream(FENstring);

    std::string board;
    char side;
    std::string castling;
    std::string enPassant;
    int halfmove;
    int fullmove;

    stream >> board >> side >> castling >> enPassant >> halfmove >> fullmove;

    for (char c : board) {

        if (c == '/') {
            continue;
        }

        if (c >= '0' && c <= '9') {
            index += c - '0';
            continue;
        }

        Color color = (c >= 'A' && c <= 'Z') ? Color::WHITE : Color::BLACK;

        position.getPieceBoard(color, charToPieceType(std::tolower(c))) |=
                    squareToBitboard(static_cast<Square>(index));

        index += 1;
    }

    position.sideToMove = (side == 'w') ? Color::WHITE : Color::BLACK;

    std::uint8_t rights = 0;
    for (char c : castling) {
        rights = addCastlingRight(c, rights);
    }
    position.castlingRights = rights;

    if (enPassant == "-") {
        position.enPassantSquare = std::nullopt;
    } else {
        position.enPassantSquare = fileRankToSquare(enPassant[0], enPassant[1] - '0');
    }

    position.halfMoveClock = halfmove;
    position.fullMoveNumber = fullmove;

    return position;
}