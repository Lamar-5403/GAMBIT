#include <gambit/attack.h>

namespace attacks {

    std::array<Bitboard, NUM_SQUARES> whitePawnAttackTable = {0};
    std::array<Bitboard, NUM_SQUARES> blackPawnAttackTable = {0};
    std::array<Bitboard, NUM_SQUARES> knightAttackTable = {0};
    std::array<Bitboard, NUM_SQUARES> kingAttackTable = {0};

    void initializeWhitePawnAttackTable() {
        for (int i = 0; i < NUM_SQUARES; i++) {
            Bitboard attackSquares = 0;
            char file = squareToFile(static_cast<Square>(i));
            int rank = squareToRank(static_cast<Square>(i));

            if (rank < 8 && rank > 1) {
                if (file != 'A') {
                    attackSquares |= squareToBitboard(static_cast<Square>(i - 9));
                }

                if (file != 'H') {
                    attackSquares |= squareToBitboard(static_cast<Square>(i - 7));
                }
            }

            whitePawnAttackTable[i] = attackSquares;
        }
    }

    void initializeBlackPawnAttackTable() {
        for (int i = 0; i < NUM_SQUARES; i++) {
            Bitboard attackSquares = 0;
            char file = squareToFile(static_cast<Square>(i));
            int rank = squareToRank(static_cast<Square>(i));

            if (rank > 1 && rank < 8) {
                if (file != 'A') {
                    attackSquares |= squareToBitboard(static_cast<Square>(i + 7));
                }

                if (file != 'H') {
                    attackSquares |= squareToBitboard(static_cast<Square>(i + 9));
                }
            }

            blackPawnAttackTable[i] = attackSquares;
        }
    }


    const std::array<std::pair<int, int>, 8> knightOffsets = {{
        {-2, -1},
        {-2,  1},
        {-1, -2},
        {-1,  2},
        { 1, -2},
        { 1,  2},
        { 2, -1},
        { 2,  1}
    }};

    void initializeKnightAttackTable() {
        for (int i = 0; i < NUM_SQUARES; i++) {
            Bitboard attackSquares = 0;
            char file = squareToFile(static_cast<Square>(i));
            int rank = squareToRank(static_cast<Square>(i));

            for (const auto& [rankOffset, fileOffset] : knightOffsets) {
                int destinationRank = rank + rankOffset;
                char destinationFile = file + fileOffset;

                if (destinationRank >= 1 && destinationRank <= 8) {
                    if (destinationFile >= 'A' && destinationFile <= 'H') {
                        attackSquares |= squareToBitboard(fileRankToSquare(destinationFile, destinationRank));
                    }
                }
            }

            knightAttackTable[i] = attackSquares;
        }
    }

    const std::array<std::pair<int, int>, 8> kingOffsets = {{
        {-1,  -1},
        { 0,  -1},
        { 1,  -1},
        {-1,   0},
        { 1,   0},
        {-1,   1},
        { 0,   1},
        { 1,   1}
    }};

    void initializeKingAttackTable() {
        for (int i = 0; i < NUM_SQUARES; i++) {
            Bitboard attackSquares = 0;
            char file = squareToFile(static_cast<Square>(i));
            int rank = squareToRank(static_cast<Square>(i));

            for (const auto& [rankOffset, fileOffset] : kingOffsets) {
                int destinationRank = rank + rankOffset;
                char destinationFile = file + fileOffset;

                if (destinationRank >= 1 && destinationRank <= 8) {
                    if (destinationFile >= 'A' && destinationFile <= 'H') {
                        attackSquares |= squareToBitboard(fileRankToSquare(destinationFile, destinationRank));
                    }
                }
            }

            kingAttackTable[i] = attackSquares;
        }
    }

}