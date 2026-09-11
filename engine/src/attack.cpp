#include <gambit/attack.h>

namespace attacks {

    std::array<Bitboard, NUM_SQUARES> knight = {0};

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

    void initializeKnightAttacks() {
        for (int i = 0; i < NUM_SQUARES; i++) {
            Bitboard attackSquares = 0;
            int rank = squareToRank(static_cast<Square>(i));
            char file = squareToFile(static_cast<Square>(i));

            for (const auto& [rankOffset, fileOffset] : knightOffsets) {
                int destinationRank = rank + rankOffset;
                char destinationFile = file + fileOffset;

                if (destinationRank >= 1 && destinationRank <= 8) {
                    if (destinationFile >= 'A' && destinationFile <= 'H') {
                        attackSquares |= squareToBitboard(fileRankToSquare(destinationFile, destinationRank));
                    }
                }
            }

            knight[i] = attackSquares;
        }
    }
}