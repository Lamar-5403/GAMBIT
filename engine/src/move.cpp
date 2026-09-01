#include <gambit/move.h>
#include <gambit/board.h>
#include <gambit/position.h>
#include <optional>
#include <bit>

void makeMove(Position& position, const Move& move) {
    Bitboard& pieceBoard = position.getPieceBoard(move.color, move.piece);

    pieceBoard = clearSquare(pieceBoard, move.source);
    pieceBoard = setSquare(pieceBoard, move.destination);
}

void unmakeMove(Position& position, const Move& move) {
    Bitboard& pieceBoard = position.getPieceBoard(move.color, move.piece);

    pieceBoard = clearSquare(pieceBoard, move.destination);
    pieceBoard = setSquare(pieceBoard, move.source);
}

void generatePawnMoves(const Position& position, std::vector<Move>& moves) {
    for (Color color : {Color::WHITE, Color::BLACK}) {
        Bitboard pawns = position.getPieceBoard(color, PieceType::PAWN);

        int direction = (color == Color::WHITE) ? -8 : 8;
        int startingRank = (color == Color::WHITE) ? 2 : 7;

        while (pawns != 0) {
            int squareIndex = std::countr_zero(pawns);

            Square source = static_cast<Square>(squareIndex);
            Square destination;

            if (squareToRank(source) == startingRank) {
                // move 2*direction == pseudo-legal
                destination = static_cast<Square>(static_cast<int>(source) + 2 * direction);

                Move move {
                    source,
                    destination,
                    color,
                    PieceType::PAWN,
                    MoveType::DOUBLE_PAWN_PUSH,
                    std::nullopt
                };

                moves.push_back(move);
            }

            destination = static_cast<Square>(static_cast<int>(source) + direction);

            Move move {
                source,
                destination,
                color,
                PieceType::PAWN,
                MoveType::QUIET,
                std::nullopt
            };

            moves.push_back(move);

            pawns &= pawns - 1;
        }
    }
}

void generateKnightMoves(const Position& position, std::vector<Move>& moves) {
    
}

void generateBishopMoves(const Position& position, std::vector<Move>& moves) {
    
}

void generateRookMoves(const Position& position, std::vector<Move>& moves) {
    
}

void generateQueenMoves(const Position& position, std::vector<Move>& moves) {
    
}

void generateKingMoves(const Position& position, std::vector<Move>& moves) {
    
}

std::vector<Move> generatePseudoLegalMoves(const Position& position) {
    std::vector<Move> moves;

    generatePawnMoves(position, moves);
    generateKnightMoves(position, moves);
    generateBishopMoves(position, moves);
    generateRookMoves(position, moves);
    generateQueenMoves(position, moves);
    generateKingMoves(position, moves);

    return moves;
}