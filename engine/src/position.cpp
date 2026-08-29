#include <gambit/position.h>

Position::Position()
    : pieces{}, sideToMove(Color::WHITE), castlingRights(0b00001111), enPassantSquare(std::nullopt), halfMoveClock(0), fullMoveNumber(1)
{
}