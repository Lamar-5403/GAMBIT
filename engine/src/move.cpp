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

void generateSlidingMoves(Bitboard ray, attacks::RayDirection direction, Square source, PieceType piece, Color color, Bitboard enemyOccupancy, Bitboard friendlyOccupancy, Bitboard allOccupancy, std::vector<Move>& moves) {
    std::optional<Square> firstBlocker = attacks::getFirstBlocker(ray, allOccupancy, direction);
    if (firstBlocker) {
            ray = attacks::truncateRay(ray, *firstBlocker, direction);
        }
    ray &= ~friendlyOccupancy;
    
    while (ray != 0) {
        int destination = std::countr_zero(ray);
        MoveType moveType = isSquareOccupied(enemyOccupancy, static_cast<Square>(destination)) ? MoveType::CAPTURE : MoveType::QUIET;

        Move move = {
            source,
            static_cast<Square>(destination),
            color,
            piece,
            moveType,
            std::nullopt
        };

        moves.push_back(move);

        ray &= ray - 1;
    }
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
    Bitboard friendlyOccupancy = (color == Color::WHITE) ? position.getOccupancy(Color::WHITE) : position.getOccupancy(Color::BLACK);
    Bitboard allOccupancy = position.getAllOccupancy();
    Bitboard bishops = position.getPieceBoard(color, PieceType::BISHOP);

    while (bishops != 0) {
        int squareIndex =  std::countr_zero(bishops);
        Square source = static_cast<Square>(squareIndex);

        Bitboard northEastRay = attacks::slidingRayTable[squareIndex].northEast;
        generateSlidingMoves(northEastRay, attacks::RayDirection::NORTH_EAST, source, PieceType::BISHOP, color, enemyOccupancy, friendlyOccupancy, allOccupancy, moves);
        
        Bitboard northWestRay = attacks::slidingRayTable[squareIndex].northWest;
        generateSlidingMoves(northWestRay, attacks::RayDirection::NORTH_WEST, source, PieceType::BISHOP, color, enemyOccupancy, friendlyOccupancy, allOccupancy, moves);

        Bitboard southEastRay = attacks::slidingRayTable[squareIndex].southEast;
        generateSlidingMoves(southEastRay, attacks::RayDirection::SOUTH_EAST, source, PieceType::BISHOP, color, enemyOccupancy, friendlyOccupancy, allOccupancy, moves);

        Bitboard southWestRay = attacks::slidingRayTable[squareIndex].southWest;
        generateSlidingMoves(southWestRay, attacks::RayDirection::SOUTH_WEST, source, PieceType::BISHOP, color, enemyOccupancy, friendlyOccupancy, allOccupancy, moves);

        bishops &= bishops - 1;
    }
}

void generateRookMoves(const Position& position, std::vector<Move>& moves) {
    Color color = position.getSideToMove();
    Bitboard enemyOccupancy = (color == Color::WHITE) ? position.getOccupancy(Color::BLACK) : position.getOccupancy(Color::WHITE);
    Bitboard friendlyOccupancy = (color == Color::WHITE) ? position.getOccupancy(Color::WHITE) : position.getOccupancy(Color::BLACK);
    Bitboard allOccupancy = position.getAllOccupancy();
    Bitboard rooks = position.getPieceBoard(color, PieceType::ROOK);

    while (rooks != 0) {
        int squareIndex = std::countr_zero(rooks);
        Square source = static_cast<Square>(squareIndex);

        Bitboard northRay = attacks::slidingRayTable[squareIndex].north;
        generateSlidingMoves(northRay, attacks::RayDirection::NORTH, source, PieceType::ROOK, color, enemyOccupancy, friendlyOccupancy, allOccupancy, moves);

        Bitboard southRay = attacks::slidingRayTable[squareIndex].south;
        generateSlidingMoves(southRay, attacks::RayDirection::SOUTH, source, PieceType::ROOK, color, enemyOccupancy, friendlyOccupancy, allOccupancy, moves);

        Bitboard eastRay = attacks::slidingRayTable[squareIndex].east;
        generateSlidingMoves(eastRay, attacks::RayDirection::EAST, source, PieceType::ROOK, color, enemyOccupancy, friendlyOccupancy, allOccupancy, moves);

        Bitboard westRay = attacks::slidingRayTable[squareIndex].west;
        generateSlidingMoves(westRay, attacks::RayDirection::WEST, source, PieceType::ROOK, color, enemyOccupancy, friendlyOccupancy, allOccupancy, moves);

        rooks &= rooks - 1;
    }
}

void generateQueenMoves(const Position& position, std::vector<Move>& moves) {
    Color color = position.getSideToMove();
    Bitboard enemyOccupancy = (color == Color::WHITE) ? position.getOccupancy(Color::BLACK) : position.getOccupancy(Color::WHITE);
    Bitboard friendlyOccupancy = (color == Color::WHITE) ? position.getOccupancy(Color::WHITE) : position.getOccupancy(Color::BLACK);
    Bitboard allOccupancy = position.getAllOccupancy();
    Bitboard queens = position.getPieceBoard(color, PieceType::QUEEN);

    while (queens != 0) {
        int squareIndex = std::countr_zero(queens);
        Square source = static_cast<Square>(squareIndex);

        Bitboard northRay = attacks::slidingRayTable[squareIndex].north;
        generateSlidingMoves(northRay, attacks::RayDirection::NORTH, source, PieceType::QUEEN, color, enemyOccupancy, friendlyOccupancy, allOccupancy, moves);

        Bitboard southRay = attacks::slidingRayTable[squareIndex].south;
        generateSlidingMoves(southRay, attacks::RayDirection::SOUTH, source, PieceType::QUEEN, color, enemyOccupancy, friendlyOccupancy, allOccupancy, moves);

        Bitboard eastRay = attacks::slidingRayTable[squareIndex].east;
        generateSlidingMoves(eastRay, attacks::RayDirection::EAST, source, PieceType::QUEEN, color, enemyOccupancy, friendlyOccupancy, allOccupancy, moves);

        Bitboard westRay = attacks::slidingRayTable[squareIndex].west;
        generateSlidingMoves(westRay, attacks::RayDirection::WEST, source, PieceType::QUEEN, color, enemyOccupancy, friendlyOccupancy, allOccupancy, moves);

        Bitboard northEastRay = attacks::slidingRayTable[squareIndex].northEast;
        generateSlidingMoves(northEastRay, attacks::RayDirection::NORTH_EAST, source, PieceType::QUEEN, color, enemyOccupancy, friendlyOccupancy, allOccupancy, moves);
        
        Bitboard northWestRay = attacks::slidingRayTable[squareIndex].northWest;
        generateSlidingMoves(northWestRay, attacks::RayDirection::NORTH_WEST, source, PieceType::QUEEN, color, enemyOccupancy, friendlyOccupancy, allOccupancy, moves);

        Bitboard southEastRay = attacks::slidingRayTable[squareIndex].southEast;
        generateSlidingMoves(southEastRay, attacks::RayDirection::SOUTH_EAST, source, PieceType::QUEEN, color, enemyOccupancy, friendlyOccupancy, allOccupancy, moves);

        Bitboard southWestRay = attacks::slidingRayTable[squareIndex].southWest;
        generateSlidingMoves(southWestRay, attacks::RayDirection::SOUTH_WEST, source, PieceType::QUEEN, color, enemyOccupancy, friendlyOccupancy, allOccupancy, moves);

        queens &= queens - 1;
    }
}

void generatePseudoLegalMoves(const Position& position, std::vector<Move>& moves) {
    generatePawnMoves(position, moves);
    generateKnightMoves(position, moves);
    generateBishopMoves(position, moves);
    generateRookMoves(position, moves);
    generateQueenMoves(position, moves);
    generateKingMoves(position, moves);
}