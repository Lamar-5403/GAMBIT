#pragma once
#include <cstdint>
#include <optional>
#include <gambit/board.h>

class Position {
    public:
        Position();

        friend bool testStartingPosition();

        Bitboard& getPieceBoard(Color color, PieceType piece);
        const Bitboard& getPieceBoard(Color color, PieceType piece) const;

    private:
        Bitboard pieces[2][6];
        Color sideToMove;
        std::uint8_t castlingRights;
        std::optional<Square> enPassantSquare;
        int halfMoveClock;
        int fullMoveNumber;

        void initializeStartingPosition();
};