#pragma once
#include <gambit/position.h>
#include <optional>
#include <vector>

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

std::ostream& operator<<(std::ostream& os, Move move);

void makeMove(Position& position, const Move& move);
void unmakeMove(Position& position, const Move& move);

void generatePawnMoves(const Position& position, std::vector<Move>& moves);
void generateKnightMoves(const Position& position, std::vector<Move>& moves);
void generateBishopMoves(const Position& position, std::vector<Move>& moves);
void generateRookMoves(const Position& position, std::vector<Move>& moves);
void generateQueenMoves(const Position& position, std::vector<Move>& moves);
void generateKingMoves(const Position& position, std::vector<Move>& moves);
std::vector<Move> generatePseudoLegalMoves(const Position& position);