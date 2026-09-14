#include <gambit/move.h>
#include <gambit/attack.h>
#include <optional>
#include <bit>

std::ostream& operator<<(std::ostream& os, Move move) {
    os << move.color << " " << move.piece << ": " << move.source << " -> " << move.destination;
    return os;
}

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

    Bitboard enemyOccupancy = (color == Color::WHITE) ? position.getOccupancy(Color::BLACK) : position.getOccupancy(Color::WHITE);
    Bitboard allOccupancy = position.getAllOccupancy();
    Bitboard enemyPawns = position.getPieceBoard(color == Color::WHITE ? Color::BLACK : Color::WHITE, PieceType::PAWN);

    Bitboard pawns = position.getPieceBoard(color, PieceType::PAWN);
    PieceType promotionPieces[4] = {PieceType::BISHOP, PieceType::KNIGHT, PieceType::ROOK, PieceType::QUEEN};

    int direction = (color == Color::WHITE) ? -BOARD_SIZE : BOARD_SIZE;
    int startingRank = (color == Color::WHITE) ? 2 : 7;
    int promotionRank = (color == Color::WHITE) ? 8 : 1;

    while (pawns != 0) {
        int squareIndex = std::countr_zero(pawns);

        Square source = static_cast<Square>(squareIndex);
        int rank = squareToRank(source);

        Square oneSquareDestination = static_cast<Square>(static_cast<int>(source) + direction);
        Square twoSquareDestination = static_cast<Square>(static_cast<int>(source) + 2 * direction);

        // standard pawn push
        if (!isSquareOccupied(allOccupancy, oneSquareDestination)) {
            if (squareToRank(oneSquareDestination) == promotionRank) {

                for (PieceType promotionPiece : promotionPieces) {
                    Move move {
                        source,
                        oneSquareDestination,
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
                    oneSquareDestination,
                    color,
                    PieceType::PAWN,
                    MoveType::QUIET,
                    std::nullopt
                };

                moves.push_back(move);

                if (rank == startingRank && !isSquareOccupied(allOccupancy, twoSquareDestination)) {

                    Move move {
                        source,
                        twoSquareDestination,
                        color,
                        PieceType::PAWN,
                        MoveType::DOUBLE_PAWN_PUSH,
                        std::nullopt
                    };

                    moves.push_back(move);
                }
            }
            
        }

        Bitboard attackSquares = (color == Color::WHITE) ? attacks::whitePawnAttackTable[squareIndex] : attacks::blackPawnAttackTable[squareIndex];
        std::optional<Square> targetSquare = position.getEnPassantSquare();

        if (targetSquare) {
            Square target = *targetSquare;
            
            int capturedPawnOffset = (color == Color::WHITE) ? 8 : -8;
            
            if ((squareToBitboard(target) & attackSquares) && (isSquareOccupied(enemyPawns, static_cast<Square>(static_cast<int>(target) + capturedPawnOffset)))) {
                Move move {
                    source,
                    target,
                    color,
                    PieceType::PAWN,
                    MoveType::EN_PASSANT,
                    std::nullopt
                };

                moves.push_back(move);
            }
        }

        attackSquares &= enemyOccupancy;

        while (attackSquares != 0) {
            int destinationSquare = std::countr_zero(attackSquares);

            if (squareToRank(static_cast<Square>(destinationSquare)) == promotionRank) {
                for (PieceType promotionPiece : promotionPieces) {
                        Move move {
                            source,
                            static_cast<Square>(destinationSquare),
                            color,
                            PieceType::PAWN,
                            MoveType::PROMOTION_CAPTURE,
                            promotionPiece
                        };

                        moves.push_back(move);
                }
            } else {
                Move move {
                        source,
                        static_cast<Square>(destinationSquare),
                        color,
                        PieceType::PAWN,
                        MoveType::CAPTURE,
                        std::nullopt
                    };

                    moves.push_back(move);
            }

            attackSquares &= attackSquares - 1;
        }

        pawns &= pawns - 1;
    }
}

void generateKnightMoves(const Position& position, std::vector<Move>& moves) {
    Color color = position.getSideToMove();

    Bitboard enemyOccupancy = (color == Color::WHITE) ? position.getOccupancy(Color::BLACK) : position.getOccupancy(Color::WHITE);
    Bitboard friendlyOccupancy = (color == Color::WHITE) ? position.getOccupancy(Color::WHITE) : position.getOccupancy(Color::BLACK);

    Bitboard knights = position.getPieceBoard(color, PieceType::KNIGHT);

    while (knights != 0) {
        int squareIndex = std::countr_zero(knights);
        Square source = static_cast<Square>(squareIndex);
        Bitboard attackSquares = attacks::knightAttackTable[squareIndex];
        attackSquares &= ~friendlyOccupancy;

        while (attackSquares != 0) {
            int destinationSquare = std::countr_zero(attackSquares);

            MoveType moveType;

            if (squareToBitboard(static_cast<Square>(destinationSquare)) & enemyOccupancy) {
                moveType = MoveType::CAPTURE;
            } else {
                moveType = MoveType::QUIET;
            }

            Move move {
                    source,
                    static_cast<Square>(destinationSquare),
                    color,
                    PieceType::KNIGHT,
                    moveType,
                    std::nullopt
            };

            moves.push_back(move);

            attackSquares &= attackSquares - 1;
        }

        knights &= knights - 1;
    }
}

void generateKingMoves(const Position& position, std::vector<Move>& moves) {
    Color color = position.getSideToMove();

    Bitboard enemyOccupancy = (color == Color::WHITE) ? position.getOccupancy(Color::BLACK) : position.getOccupancy(Color::WHITE);
    Bitboard friendlyOccupancy = (color == Color::WHITE) ? position.getOccupancy(Color::WHITE) : position.getOccupancy(Color::BLACK);

    Bitboard kingBoard = position.getPieceBoard(color, PieceType::KING);
    int squareIndex = std::countr_zero(kingBoard);
    Square source = static_cast<Square>(squareIndex);

    Bitboard attackSquares = attacks::kingAttackTable[squareIndex];
    attackSquares &= ~friendlyOccupancy;

    while (attackSquares != 0) {
        int destinationSquare = std::countr_zero(attackSquares);

        MoveType moveType;

        if (squareToBitboard(static_cast<Square>(destinationSquare)) & enemyOccupancy) {
            moveType = MoveType::CAPTURE;
        } else {
            moveType = MoveType::QUIET;
        }

        Move move {
                source,
                static_cast<Square>(destinationSquare),
                color,
                PieceType::KING,
                moveType,
                std::nullopt
        };

        moves.push_back(move);

        attackSquares &= attackSquares - 1;
    }

    // - appropriate castling-rights bit exists
    // - king is on its starting square
    // - rook is on its starting square
    // - squares between them are empty
    // - king is not currently in check
    // - king does not pass through an attacked square
    // - king does not end on an attacked square
}

void generateBishopMoves(const Position& position, std::vector<Move>& moves) {
    Color color = position.getSideToMove();
    Bitboard enemyOccupancy = (color == Color::WHITE) ? position.getOccupancy(Color::BLACK) : position.getOccupancy(Color::WHITE);
    Bitboard allOccupancy = position.getAllOccupancy();

    

}

void generateRookMoves(const Position& position, std::vector<Move>& moves) {
    
}

void generateQueenMoves(const Position& position, std::vector<Move>& moves) {
    
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