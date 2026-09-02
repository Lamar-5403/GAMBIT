#include <gambit/move.h>
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
    Color color = position.getSideToMove();

    Bitboard friendlyOccupancy = position.getOccupancy(color);
    Bitboard enemyOccupancy = (color == Color::WHITE) ? position.getOccupancy(Color::BLACK) : position.getOccupancy(Color::WHITE);
    Bitboard allOccupancy = position.getAllOccupancy();

    Bitboard pawns = position.getPieceBoard(color, PieceType::PAWN);
    PieceType promotionPieces[4] = {PieceType::BISHOP, PieceType::KNIGHT, PieceType::ROOK, PieceType::QUEEN};

    int direction = (color == Color::WHITE) ? -BOARD_SIZE : BOARD_SIZE;
    int startingRank = (color == Color::WHITE) ? 2 : 7;
    int promotionRank = (color == Color::WHITE) ? 8 : 1;

    while (pawns != 0) {
        int squareIndex = std::countr_zero(pawns);

        Square source = static_cast<Square>(squareIndex);
        int rank = squareToRank(source);
        char file = squareToFile(source);

        Square destination = static_cast<Square>(static_cast<int>(source) + direction);

        // standard pawn push
        if (!isSquareOccupied(allOccupancy, destination)) {
            if (squareToRank(destination) == promotionRank) {

                for (PieceType promotionPiece : promotionPieces) {
                    Move move {
                        source,
                        destination,
                        color,
                        PieceType::PAWN,
                        MoveType::PROMOTION,
                        promotionPiece
                    };

                    moves.push_back(move);
                }

            } else {
                Move move {
                    source,
                    destination,
                    color,
                    PieceType::PAWN,
                    MoveType::QUIET,
                    std::nullopt
                };

                moves.push_back(move);

                if (rank == startingRank && (!isSquareOccupied(allOccupancy, static_cast<Square>(static_cast<int>(source) + 2*direction)))) {
                    destination = static_cast<Square>(static_cast<int>(source) + 2*direction);

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
            }
            
        }

        
        //pawn capture
        if (isSquareOccupied(enemyOccupancy, static_cast<Square>(static_cast<int>(source) + (direction - 1)))) {
            Move move {
                source,
                destination,
                color,
                PieceType::PAWN,
                MoveType::CAPTURE,
                std::nullopt
            };

            moves.push_back(move);
        } else if (isSquareSet(position.getOccupancy(Color::BLACK), static_cast<Square>(static_cast<int>(source) + (direction + 1)))) {
            Move move {
                source,
                destination,
                color,
                PieceType::PAWN,
                MoveType::CAPTURE,
                std::nullopt
            };

            moves.push_back(move);
        }










        // promotion capture
        if (isSquareSet(position.getOccupancy(Color::BLACK), static_cast<Square>(static_cast<int>(source) + (BOARD_SIZE - 1))) && squareToRank(static_cast<Square>(static_cast<int>(source) + 8)) == 8) {
            Move move {
                source,
                destination,
                color,
                PieceType::PAWN,
                MoveType::PROMOTION_CAPTURE,
                PieceType::QUEEN      // soon to implement a menu option for other pieceTypes
            };

            moves.push_back(move);
        } else if (isSquareSet(position.getOccupancy(Color::BLACK), static_cast<Square>(static_cast<int>(source) + (BOARD_SIZE + 1))) && squareToRank(static_cast<Square>(static_cast<int>(source) + 8)) == 8) {
            Move move {
                source,
                destination,
                color,
                PieceType::PAWN,
                MoveType::PROMOTION_CAPTURE,
                PieceType::QUEEN      // soon to implement a menu option for other pieceTypes
            };

            moves.push_back(move);
        }

        //en passant
        const Square* enPassantSquare = position.getEnPassantSquare();

        if (enPassantSquare != nullptr) {
            Move move {
                source,
                *enPassantSquare,
                color,
                PieceType::PAWN,
                MoveType::EN_PASSANT,
                std::nullopt
            };

            moves.push_back(move);
        }


        pawns &= pawns - 1;
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