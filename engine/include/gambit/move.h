#pragma once
#include <gambit/board.h>
#include <gambit/position.h>
#include <optional>

enum class MoveType {
    QUIET,
    CAPTURE,
    DOUBLE_PAWN_PUSH,
    EN_PASSANT,
    CASTLE,
    PROMOTION,
    PROMOTION_CAPTURE
};

struct Move {
    Square source;
    Square destination;
    Color color;
    PieceType piece;
    MoveType type;
    std::optional<PieceType> promotionPiece;
};

void makeMove(Position& position, const Move& move);
void unmakeMove(Position& position, const Move& move);
