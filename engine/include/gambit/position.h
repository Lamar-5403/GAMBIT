#pragma once
#include <cstdint>
#include <optional>
#include <gambit/board.h>
#include <string>

class Position {
    public:
        Position();

        static Position starting();

        friend Position positionFromFEN(std::string FENstring);

        Bitboard& getPieceBoard(Color color, PieceType piece);
        const Bitboard& getPieceBoard(Color color, PieceType piece) const;
        Bitboard getOccupancy(Color color) const;
        Bitboard getAllOccupancy() const;

        Color getSideToMove() const;
        std::uint8_t getCastlingRights() const;
        std::optional<Square> getEnPassantSquare() const;
        int getHalfMoveClock() const;
        int getFullMoveNumber() const;
        
    private:
        Bitboard pieces[2][6];
        Color sideToMove;
        std::uint8_t castlingRights;
        std::optional<Square> enPassantSquare;
        int halfMoveClock;
        int fullMoveNumber;
        
        void initializeStartingPosition();
};