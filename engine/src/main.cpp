bool testBoard();
bool testRank();
bool testFile();
bool testStartingPosition();
bool testFileRankToSquare();
bool testMakeMove();
bool testForwardPawnMove();
bool testStartingPositionFromFEN();
bool testPositionFromFEN();
bool testWhitePawnAttackTable();
bool testBlackPawnAttackTable();
bool testPseudoLegalPawnMoves();
bool testKnightAttackTable();
bool testKingAttackTable();
bool testPseudoLegalKnightMoves();
bool testEnPassant();

int main() {
    bool passed = true;

    passed &= testBoard();
    passed &= testFile();
    passed &= testRank();
    passed &= testStartingPosition();
    passed &= testFileRankToSquare();
    passed &= testMakeMove();
    passed &= testForwardPawnMove();
    passed &= testStartingPositionFromFEN();
    passed &= testPositionFromFEN();
    passed &= testWhitePawnAttackTable();
    passed &= testBlackPawnAttackTable();
    passed &= testPseudoLegalPawnMoves();
    passed &= testKnightAttackTable();
    passed &= testKingAttackTable();
    passed &= testPseudoLegalKnightMoves();
    passed &= testEnPassant();
    return passed ? 0 : 1;
}