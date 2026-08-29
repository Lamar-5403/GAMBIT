#include <cstdint>
#include <optional>
#include <gambit/board.h>

class Position {
    private:
        Bitboard pieces[2][6];
        Color sideToMove;
        std::uint8_t castlingRights;
        std::optional<Square> enPassantSquare;
        int halfMoveClock;
        int fullMoveNumber;

        void initializeStartingPosition();

        Bitboard& getPieceBoard(Color color, PieceType piece);

    public:
        Position();

        friend bool testStartingPosition();
};