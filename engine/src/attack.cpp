#include <gambit/attack.h>

namespace attacks {

    std::array<Bitboard, NUM_SQUARES> whitePawnAttackTable = {0};
    std::array<Bitboard, NUM_SQUARES> blackPawnAttackTable = {0};
    std::array<Bitboard, NUM_SQUARES> knightAttackTable = {0};
    std::array<Bitboard, NUM_SQUARES> kingAttackTable = {0};
    std::array<SlidingRays, NUM_SQUARES> slidingRayTable = {0};

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

    const std::array<std::pair<int, int>, 8> rayDirections = {{
        { 1,   0}, // N
        {-1,   0}, // S
        { 0,   1}, // E
        { 0,  -1}, // W
        { 1,   1}, // NE
        { 1,  -1}, // NW
        {-1,   1}, // SE
        {-1,  -1}  // SW
    }};

    void initializeSlidingRayTable() {
        for (int i = 0; i < NUM_SQUARES; i++) {
            SlidingRays rays = {};
            Square source = static_cast<Square>(i);
            int rank = squareToRank(source);
            char file = squareToFile(source);

            for (std::size_t direction = 0; direction < rayDirections.size(); direction++) {
                const auto& [rankOffset, fileOffset] = rayDirections[direction];
                Bitboard raySquares = 0;
                int targetRank = rank + rankOffset;
                char targetFile = file + fileOffset;

                while (targetRank >= 1 && targetRank <= 8 && targetFile >= 'A' && targetFile <= 'H') {
                    raySquares |= squareToBitboard(fileRankToSquare(targetFile, targetRank));
                    targetRank += rankOffset;
                    targetFile += fileOffset;
                }

                switch (direction) {
                    case 0:
                        rays.north = raySquares;
                    break;

                    case 1:
                        rays.south = raySquares;
                    break;

                    case 2:
                        rays.east = raySquares;
                    break;

                    case 3:
                        rays.west = raySquares;
                    break;

                    case 4:
                        rays.northEast = raySquares;
                    break;

                    case 5:
                        rays.northWest = raySquares;
                    break;

                    case 6:
                        rays.southEast = raySquares;
                    break;

                    case 7:
                        rays.southWest = raySquares;
                    break;
                }
            }

            slidingRayTable[i] = rays;
        }
    }

    std::optional<Square> getFirstBlocker(Bitboard ray, Bitboard occupancy, RayDirection direction) {
        Bitboard blockers = ray & occupancy;

        if (blockers == 0) {
            return std::nullopt;
        }

        if (direction == RayDirection::NORTH || direction == RayDirection::WEST
            || direction == RayDirection::NORTH_EAST || direction == RayDirection::NORTH_WEST) {
                return static_cast<Square>(63 - std::countl_zero(blockers));
        }

        return static_cast<Square>(std::countr_zero(blockers));
    }
}